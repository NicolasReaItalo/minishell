/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:33:31 by joyeux            #+#    #+#             */
/*   Updated: 2024/05/03 16:08:06 by tjoyeux          ###   ########.fr       */
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

static int	unimplemented_special_var(char c)
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

char	*dollar_sign(char **str, char **next, int *len)
{
	if (**str == '$' && *(*str + 1) == '?')
		return (**str = '\0', *next = *str + 2, ft_substr(*str + 1, 0, 1));
	else if (**str == '$' && (is_valid_first_param_char(*(*str + 1))))
	{
		**str = '\0';
		(*str)++;
		while (*(*str + *len) && is_valid_param_char(*(*str + *len)))
			(*len)++;
		*next = *str + *len;
		return (ft_substr(*str, 0, *len));
	}
	else if (**str == '$' && (*(*str + 1) == '\'' || *(*str + 1) == '\"'))
	{
		**str = '\0';
		(*str)++;
		return (*next = *str, ft_strdup(*str));
	}
	else if (**str == '$' && unimplemented_special_var(*(*str + 1)))
	{
		**str = '\0';
		(*str)++;
		*next = *str + 1;
		return (ft_substr(*str, 0, 1));
	}
	return (NULL);
}

//TODO: diviser find_next_param_expansion
/*
static char	*find_next_param_exp_oper(char *str, char **next, int *in_quotes)
{

}
*/