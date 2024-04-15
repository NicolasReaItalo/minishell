/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquotting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:08:30 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/15 09:29:41 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"
#include "stdio.h"
#include "libft.h"

//Concatene 3 chaines de caracteres
// first alloue, second, third non alloue
static char	*ft_concat_3str(char *first, char *second, char *third, int len)
{
	// char	*output;  // commente pour ne pas avoir d'ereeur de compilation
	// char	*first_concat; // commente pour ne pas avoir d'ereeur de compilation

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
				ptr2++;
			*ptr1 = '\0';
			*ptr2 = '\0';
			content = ft_concat_3str(content, ptr1 + 1, ptr2 + 1, size);
			ptr1 = ptr2 - 1;
		}
		else
			ptr1++;
	}
}

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
					unquote_content(original_content);
					return (1);
				}
				content++;
			}
		}
		content++;
	}
	unquote_content(original_content);
	return (0);
}
/*
int	main(int argc, char **argv)
{
		if (argc = 1)
		printf("Argument reçu : %s\n", argv[1]);
	if (pathname_in_quotes(argv[1]) == 1)
		printf("INVALID %s\n", argv[1]);
	else
		printf("VALID %s\n", argv[1]);
}
*/
