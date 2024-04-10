/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:07:19 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/10 11:40:31 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*bptr;
	char	*new;
	int		i_end;

	if (!s1)
		return (NULL);
	bptr = (char *)s1;
	while (is_in_set(*bptr, set) && *bptr != '\0')
		bptr++;
	if (*bptr == '\0')
	{
		new = malloc(sizeof(char));
		if (!new)
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	i_end = ft_strlen(bptr) - 1;
	while (is_in_set(bptr[i_end], set))
		i_end--;
	new = malloc(sizeof(char) * (i_end + 2));
	if (!new)
		return (NULL);
	ft_strlcpy(new, bptr, i_end + 2);
	return (new);
}
