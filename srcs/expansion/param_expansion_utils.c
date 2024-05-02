/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:33:31 by joyeux            #+#    #+#             */
/*   Updated: 2024/05/02 11:40:23 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

static int	is_valid_param_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

static int	is_valid_first_param_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static int	unimplemented_special_var (char c)
{
	if (ft_isdigit(c))
		return (1);
	if (c == '-')
		return (1);
	if (c == '*')
		return (1);
	if (c == '!')
		return (1);
	if (c == '$')
		return (1);
	if (c == '#')
		return (1);
	if (c == '@')
		return (1);
	return (0);
}

//TODO: diviser find_next_param_expansion
/*
static char	*find_next_param_exp_oper(char *str, char **next, int *in_quotes)
{

}
*/

// Fonction qui prend en entree une chaine de caractere et renvoie
// une chaine ayant les criteres d'une key
char	*find_next_param_expansion(char *str, char **next, int *in_quotes)
{
	int		len;

	len = 0;
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
		else if (*str == '$' && (is_valid_first_param_char(*(str + 1))))
		{
			*str = '\0';
			str++;
			while ( *(str + len) && is_valid_param_char(*(str + len)))
				len++;
			*next = str + len;
			return (ft_substr(str, 0, len));
		}
		else if (*str == '$' && (*(str + 1) == '\'' || *(str + 1) == '\"') )
		{
			*str = '\0';
			str++;
			*next = str;
			return ( ft_strdup(str));
		}
		else if (*str == '$' && unimplemented_special_var(*(str + 1)))
		{
			*str = '\0';
			str++;
			*next = str + 1;
			return (ft_substr(str, 0, 1));
		}
		str++;
	}
	return (NULL);
}
