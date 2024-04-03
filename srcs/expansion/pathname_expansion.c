/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:29:47 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/02 15:41:24y tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"
#include <stdio.h>

// Verifie si le nom du fichier est conforme au format de l'expansion
/*static int is_valid_pathname(char *pathname, char *word)
{
	while (*word)
	{
		while (*pathname == '*' && *word)
		{
			while (*(pathname +1) == '*')
				pathname++; 
			while (*word && *(pathname + 1) != *word)
				word++;
			if (!*word && !*(pathname + 1))
				return (1);
			else if (!*word)
				return (0);
			pathname++;
		}	
		if (*pathname != *word)
			return (0);
		pathname++;
		word++;
	}
	if (!*pathname)
		return (1);
	return (0);
}*/
/*
static int	match_pattern(char *pattern, char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	else if (*pattern == '\0' || *str == '\0')
		return (0);
	if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	if (*pattern == '*' && *(pattern + 1) == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) == '*')
		return (match_pattern(pattern + 1, str));
	if (*pattern == '*' && *(pattern + 1) == *str)
		return (match_pattern(pattern + 1, str) || match_pattern(pattern, str + 1));
	else if (*pattern == '*')
		return (match_pattern(pattern, str + 1));
	else
		return (0);
}*/

static int	match_pattern(char *pattern, char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	else if (*pattern == '\0' || *str == '\0')
		return (0);
	if (*pattern == '*')
	{
		if(*(pattern + 1) == '*')
			return (match_pattern(pattern + 1, str));
		else if (*(pattern + 1) == '\0')
			return (1);
		else if (*(pattern + 1) == *str)
			return (match_pattern(pattern + 1, str) || match_pattern(pattern, str + 1));
		else 
			return (match_pattern(pattern, str + 1));
	}
	else if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	else
		return (0);
}

/*
// Creation d'un tableau de string de tous les fichiers valides
void show_directory(char *pathname)
{
	DIR	*dir;
	struct dirent	*file;
	char **words;
	
	dir = opendir(".");
	if (!dir)
		return ;
	while ((file = readdir(dir)) != NULL)
	{
		if (match_pattern(pathname, file->d_name))
			printf("%s\n", file->d_name);
	}
	closedir(dir);
}*/

int	count_valid_pathname(char *content)
{
	DIR	*dir;
	struct dirent	*file;
	int	count;

	dir = opendir(".");
	if (!dir)
		return (-1);
	count = 0;
	while ((file = readdir(dir)) != NULL)
	{
		if (match_pattern(content, file->d_name))
		{	
			count++;
//			printf("%s\n", file->d_name);
		}
	}
	closedir(dir);
//	printf("\nnumber of valid files : %d\n\n", count);
	return (count);
}

char **create_pathname_tab(t_token *token)
{
	DIR	*dir;
	struct dirent	*file;
	int	count;
	char	**words;
	int		i;

	i = 0;
	count = count_valid_pathname(token->content) + 1;
	words = malloc(count * sizeof(char *));
	if (!words)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while ((file = readdir(dir)) != NULL)
	{
		if (match_pattern(token->content, file->d_name))
		{	
			words[i] = ft_strdup(file->d_name);
//			printf("\"%s\" put in tab\n", file->d_name);
			i++;
		}
	}
	words[i] = NULL;
	closedir(dir);
//	printf("PRETEST : %s\n", words[0]);
	return (words);

}

int	expand_pathname_cmd(t_token *token)
{
	char	**words;
	char	*tmp;
	t_token	*ptr;

	words = create_pathname_tab(token);
	if (!words)
		return (1);
	tmp = token->content;
//	printf ("TEST : %s\n", *words);
	token->content = ft_strdup(*words);
	free (tmp);
	ptr = token;
	words_to_token(&ptr, words);
	free_words_tab(&words);
	return (0);

/*	DIR	*dir;
	struct dirent	*file;
	int	count;
	char	**words;
	int		i;

	i = 0;
	count = count_valid_pathname(token->content) + 1;
	words = malloc(count * sizeof(char *));
	if (!words)
		return (1);
	dir = opendir(".");
	if (!dir)
		return (1);
	while ((file = readdir(dir)) != NULL)
	{
		if (match_pattern(token->content, file->d_name))
		{	
			words[i] = ft_strdup(file->d_name);
			printf("\"%s\" put in tab\n", file->d_name);
			i++;
		}
	}
	words [i] = NULL;
	closedir(dir);
	return (0);*/
}
/*
// Gestion de l'expansion du wildcard * pour la redirection
// Return error code
int expand_pathname_redir(t_token *token)
{	
	int	count;
	char *tmp;

	count = count_valid_pathname(token->content);
	if (token->type >= R_IN && token->type <= R_APPEND)
	{
		if (count > 1)
		// error msg: "%s: ambiguous redirect", token->content 
		else if (count == 1)
		{
			tmp = token->content;
			token->content = // Dois je utiliser un tableau, ou adapter la fonction count_valid_pathname
		}
		// change node

	}


}*/
/*
//# include <stdio.h>
int	main(int argc, char **argv)
{
//	show_directory();
//	count_valid_pathname(argv[1]);
	t_token	*test;

	test = malloc(sizeof(t_token));
	if (!test)
		return (1);
	test->content = argv[1];
	expand_pathname_cmd(test);
	return (0);
}*/
/*	if (argc == 3)
	{
		if (is_valid_pathname(argv[1], argv[2]))
			printf("Valid pathname\n");
		else
			printf("Invalid pathname\n");
	}
	show_directory(argv[1]);
	return (0);
}*/
// gcc -g3 srcs/expansion/pathname_expansion.c -I./include -I./libft -o pathname_expansion