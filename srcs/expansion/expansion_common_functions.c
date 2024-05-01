/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_common_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:02:56 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/01 11:07:59 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

static int	is_valid_param_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

// Fonction qui prend en entree une chaine de caractere et renvoie
// une chaine ayant les criteres d'une key
char	*find_next_param_expansion(char *str, char **next, int *in_quotes)
{
	int		len;

	len = 0;
	*in_quotes = 0;
	while (*str)
	{
		if (*str == '\"')
		{
			if (!*in_quotes)
				*in_quotes = 1;
			else
				*in_quotes = 0;
			str++;
			continue ;
		}
		if (!*in_quotes && *str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
		}
		else if (*str == '$' && *(str + 1) == '?')
			return (*str = '\0', *next = str + 2, ft_substr(str + 1, 0, 1));
		else if (*str == '$' && is_valid_param_char(*(str + 1)))
		{
			*str = '\0';
			str++;
			while ( *(str + len) && is_valid_param_char(*(str + len)))
				len++;
			*next = str + len;
			return (ft_substr(str, 0, len));
		}
		str++;
	}
	return (NULL);
}

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


