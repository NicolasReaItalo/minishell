/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:28:47 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/13 13:30:22 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define NB_CONVERTER 9

static void	init_conv_table(t_conv *tab, int fd)
{
	tab[0] = (t_conv){"%c", ft_print_c, fd};
	tab[1] = (t_conv){"%s", ft_print_str, fd};
	tab[2] = (t_conv){"%%", ft_print_percent, fd};
	tab[3] = (t_conv){"%i", ft_print_int, fd};
	tab[4] = (t_conv){"%d", ft_print_int, fd};
	tab[5] = (t_conv){"%u", ft_print_uint, fd};
	tab[6] = (t_conv){"%x", ft_print_hexa_lower, fd};
	tab[7] = (t_conv){"%X", ft_print_hexa_upper, fd};
	tab[8] = (t_conv){"%p", ft_print_ptr, fd};
}
// Implement la fonction is_in_tab
//return length ou -1 si pas dans la tab

static int	is_in_tab(const char *format, t_conv *tab, va_list pa
						, int *str_size)
{
	int	tab_counter;
	int	length;
	int	fd;

	fd = tab[0].fd;
	tab_counter = 0;
	while (tab_counter < NB_CONVERTER)
	{
		if (*format == tab[tab_counter].ph[0]
			&& *(format + 1) == tab[tab_counter].ph[1])
		{
			length = tab[tab_counter].f(fd, pa);
			*str_size += length;
			return (length);
		}
		tab_counter++;
	}
	return (-1);
}

// General function which go through the string
int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	pa;
	int		str_size;
	t_conv	tab_conv[NB_CONVERTER];

	va_start(pa, format);
	init_conv_table(tab_conv, fd);
	str_size = 0;
	while (*format)
	{
		if (is_in_tab(format, tab_conv, pa, &str_size) == -1)
		{
			ft_putchar_fd(format[0], fd);
			str_size++;
			format++;
		}
		else
			format += 2;
	}
	va_end(pa);
	return (str_size);
}
