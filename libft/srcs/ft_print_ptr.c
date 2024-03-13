/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:39:37 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/13 13:25:06 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	create_tab(unsigned long long n, char *tab, int i, int letter_case)
{
	tab[i] = '\0';
	if (n == 0)
	{
		tab[--i] = '0';
		return (i);
	}
	while (n)
	{
		i--;
		if (n % 16 < 10)
			tab[i] = n % 16 + 48;
		else if (n % 16 >= 10)
			tab[i] = n % 16 + letter_case;
		n /= 16;
	}
	return (i);
}

int	ft_print_ptr(int fd, va_list ap)
{
	void	*ptr;
	int		i;
	char	tab[20];

	ptr = va_arg(ap, void *);
	if (!ptr)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	i = create_tab((unsigned long long)ptr, tab, sizeof(tab) - 1, 87);
	write(fd, "0x", 2);
	write(fd, tab + i, sizeof(tab) - i - 1);
	return (2 + sizeof(tab) - i - 1);
}
