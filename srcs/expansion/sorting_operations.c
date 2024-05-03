/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:22:06 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/03 14:32:01 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

static int	ft_strcmp_no_case(char *s1, char *s2)
{
	char	*str1;
	char	*str2;
	int		i;

	str1 = ft_strdup(s1);
	str2 = ft_strdup(s2);
	i = 0;
	while (str1[i])
	{
		str1[i] = ft_tolower(str1[i]);
		i++;
	}
	i = 0;
	while (str2[i])
	{
		str2[i] = ft_tolower(str2[i]);
		i++;
	}
	i = ft_strcmp(str1, str2);
	return (free(str1), free(str2), i);
}

//Ajouter *** et tolower()
char	**sort_pathname_tab(char **tab)
{
	char	*temp;
	int		sorted;
	int		i;

	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (tab[i + 1])
		{
			if (ft_strcmp_no_case(tab[i], tab[i + 1]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
	return (tab);
}
