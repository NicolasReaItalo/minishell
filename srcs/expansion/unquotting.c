/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquotting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:08:30 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/06 13:04:21 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"
#include "stdio.h"
#include "libft.h"

int	pathname_in_quotes(char *content)
{
	char	*ptr1;
	char	*original_content;

	original_content = content;
	while (*content)
	{
		if (*content == '\'' || *content == '\"')
		{
			ptr1 = content;
			content++;
			while (*content && *content != *ptr1)
			{
				if (*content == '*')
				{
					original_content = unquote_content(original_content);
					return (1);
				}
				content++;
			}
		}
		content++;
	}
	original_content = unquote_content(original_content);
	return (0);
}
