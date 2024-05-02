/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:56:40 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/02 14:30:07 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

/*
int	get_last_word(char **words)
{
	int	i;

	if (!*words)
		return (-1);
	i = 0;
	while (words[i] != NULL)
		i++;
	return (i - 1);
}*/

static int	case_no_words(char ***words, char **tmp2, char *start, char *end)
{
	free_words_tab(words);
	*words = malloc(3 * sizeof(char *));
	if (!*words)
		return (1);
	*tmp2 = ft_strdup(start);
	*(words[0]) = ft_strdup("");
	*(words[1]) = ft_strdup(end);
	*(words[2]) = NULL;
	return (0);
}

// Gestion de l'IFS apres l'expansion des parametres
// Return 0 ou code erreur
int	field_splitting(t_token *token, char *start, char *end)
{
	char	**words;
	t_token	*ptr;
	char	*tmp2;

	words = ft_split(token->content, -1);
	ptr = token;
	if (words == NULL)
		return (1);
	if (!words[0])
	{
		if (case_no_words(&words, &tmp2, start, end))
			return (1);
	}
	else
		tmp2 = ft_strdup(words[0]);
	if (words_to_token(ptr, words, 1))
		return (1);
	free_words_tab(&words);
	free(token->content);
	token->content = tmp2;
	return (0);
}
