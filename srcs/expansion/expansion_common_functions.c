/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_common_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:02:56 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/03 13:37:31 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

void	free_words_tab(char ***words)
{
	char	**original_words;

	original_words = *words;
	while (**words)
	{
		free(**words);
		**words = NULL;
		(*words)++;
	}
	free(original_words);
	original_words = NULL;
}

// Check if there is only '*' in a string
static int	only_stars(char *pattern)
{
	while (*pattern)
	{
		if (*pattern != '*')
			return (0);
		pattern++;
	}
	return (1);
}

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

//Concatene 3 chaines de caracteres
// first alloue, second, third non alloue
static char	*ft_concat_3str(char *first, char *second, char *third, int len)
{
	ft_strlcat(first, second, len);
	ft_strlcat(first, third, len);
	return (first);
}

void	unquote_content(char *content)
{
	char	*ptr1;
	char	*ptr2;
	int		size;

	ptr1 = content;
	size = ft_strlen(content);
	while (*ptr1)
	{
		if (*ptr1 == '\'' || *ptr1 == '\"')
		{
			ptr2 = ptr1 + 1;
			while (*ptr2 != *ptr1)
			{
				if (!*ptr2)
					return ;
				ptr2++;
			}
			*ptr1 = '\0';
			*ptr2 = '\0';
			content = ft_concat_3str(content, ptr1 + 1, ptr2 + 1, size);
			ptr1 = ptr2 - 1;
		}
		else
			ptr1++;
	}
}

// Create and add new tokens in a linked list
// Add content from a tab of char*
// Return 1 if error
int	words_to_token(t_token *ptr, char **words, int i)
{
	t_token	*new;

	words++;
	while (*words)
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return (1);
		ft_memset(new, 0, sizeof(t_token));
		if (i == 1)
			new->param_expanded = 1;
		else if (i == 2)
			new->path_expanded = 1;
		new->content = ft_strdup(*words);
		new->next = ptr->next;
		ptr->next = new;
		ptr = ptr->next;
		words++;
	}
	return (0);
}
