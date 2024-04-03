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
}

// Gestion de l'expansion du wildcard *
int	expand_pathname(t_token *token)
{

}


/*
//# include <stdio.h>
int	main(int argc, char **argv)
{
//	show_directory();
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