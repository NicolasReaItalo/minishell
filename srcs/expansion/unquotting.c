/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquotting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:08:30 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/12 18:44:22 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "word_expansion.h"
#include "stdio.h"

void	unquote_content(char *content)
{
	printf("unquote %s\n", content);	
}

int	pathname_in_quotes(char *content)
{
	char	*ptr1;
	
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
					unquote_content(content);
					return (1);
				}
				content++;
			}
		}	
		content++;
	}
	unquote_content(content);
	return (0);
}
/*
int	valid_pathname(char *content)
{
	if (ft_strchr(content, '*') && !pathname_in_quotes(content))
				
		
		
		
	return (0);
}*/

int	main(int argc, char **argv)
{
	if (pathname_in_quotes(argv[1]) == 1)
		printf("INVALID\n");
	else
		printf("VALID\n");
}

