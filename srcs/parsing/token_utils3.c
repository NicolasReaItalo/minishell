/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:45:29 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/07 14:16:17 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	word_is_wspace(char *str)
{
	while (*str)
	{
		if (!is_wspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	contains_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (1);
		str++;
	}
	return (0);
}
