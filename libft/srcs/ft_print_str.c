/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:53:19 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/13 13:06:08 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(int fd, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	write(fd, str, ft_strlen(str));
	return (ft_strlen(str));
}
