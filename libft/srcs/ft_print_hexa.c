/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:39:37 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/13 13:15:26 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	create_tab(long n, char *tab, int i, int letter_case)
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

int	ft_print_hexa_lower(int fd, va_list ap)
{
	unsigned int	nb;
	int				i;
	char			tab[9];

	nb = va_arg(ap, int);
	i = create_tab(nb, tab, sizeof(tab) - 1, 87);
	write(fd, tab + i, sizeof(tab) - i - 1);
	return (sizeof(tab) - i - 1);
}

int	ft_print_hexa_upper(int fd, va_list ap)
{
	unsigned int	nb;
	int				i;
	char			tab[9];

	nb = va_arg(ap, int);
	i = create_tab(nb, tab, sizeof(tab) - 1, 55);
	write(fd, tab + i, sizeof(tab) - i - 1);
	return (sizeof(tab) - i - 1);
}
