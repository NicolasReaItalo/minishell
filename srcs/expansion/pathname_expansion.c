/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:29:47 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/30 16:56:37 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

int	match_pattern(char *pattern, char *str)
{
	if (only_stars(pattern) && *str == '\0')
		return (1);
	else if (*pattern == '\0' || *str == '\0')
		return (0);
	if (*pattern == '*')
	{
		if (*(pattern + 1) == '*')
			return (match_pattern(pattern + 1, str));
		else if (*(pattern + 1) == '\0')
			return (1);
		else if (*(pattern + 1) == *str)
			return (match_pattern(pattern + 1, str)
				|| match_pattern(pattern, str + 1));
		else
			return (match_pattern(pattern, str + 1));
	}
	else if (*pattern == *str)
		return (match_pattern(pattern + 1, str + 1));
	else
		return (0);
}

int	count_valid_pathname(char *content, t_token *token)
{
	DIR				*dir;
	struct dirent	*file;
	int				count;
	char			*str;

	dir = opendir(".");
	if (!dir)
		return (-1);
	count = 0;
	file = readdir(dir);
	while (file != NULL)
	{
		if (content[0] == '.' && content[1] == '/')
			str = content + 2;
		else
			str = content;
		token->hidden = (str[0] == '.');
		if (token->hidden || file->d_name[0] != '.')
		{
			if (match_pattern(str, file->d_name))
				count++;
		}
		file = readdir(dir);
	}
	return (closedir(dir), count);
}

static int	find_valid_files(t_token *token, struct dirent *file
	, char **words, int *i)
{
	if (token->hidden || file->d_name[0] != '.')
	{
		if (token->content[0] == '.' && token->content[1] == '/'
			&& match_pattern(token->content + 2, file->d_name))
			words[(*i)++] = ft_strjoin("./", file->d_name);
		else if (match_pattern(token->content, file->d_name))
		{
			words[*i] = ft_strdup(file->d_name);
			if (!words[(*i)++])
				return (1);
		}
	}
	return (0);
}

char	**create_pathname_tab(t_token *token)
{
	DIR				*dir;
	struct dirent	*file;
	char			**words;
	int				i;
	int				count;

	i = 0;
	count = count_valid_pathname(token->content, token) + 1;
	words = malloc(count * sizeof(char *));
	if (!words)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	file = readdir(dir);
	while (file != NULL)
	{
		if (find_valid_files(token, file, words, &i))
			return (NULL);
		file = readdir(dir);
	}
	words[i] = NULL;
	closedir(dir);
	return (words);
}

void	sort_pathname_tab(char **tab)
{
	char *temp;
	int	sorted;
	int		i;
	sorted = 0;
	while(!sorted)
	{
		i = 0;
		while (tab[i+1])
		{
			sorted = 1;
			if( ft_strcmp(tab[i], tab[i+1]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
}

int	expand_pathname_cmd(t_token *token)
{
	char	**words;
	char	*tmp;
	t_token	*ptr;

	words = create_pathname_tab(token);
	if (!words)
		return (1);
	if (!*words)
		return (free(words), 0);
	sort_pathname_tab(words);
	tmp = token->content;
	token->content = ft_strdup(*words);
	free (tmp);
	ptr = token;
	if (words_to_token(ptr, words))
		return (1);
	free_words_tab(&words);
	return (0);
}
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
