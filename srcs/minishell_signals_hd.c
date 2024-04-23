/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals_hd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:22:26 by nrea              #+#    #+#             */
/*   Updated: 2024/04/23 14:28:06 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_hd_handler(int signum)
{
	g_sig = signum;
	close(4);
	close(5);
	write(1, "\n", 1);
	exit(128 + signum);
}

int	set_hd_parent_signals(void)
{
	g_sig = 0;
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (1);
}

int	set_hd_child_signals(void)
{
	g_sig = 0;
	if (signal(SIGINT, sig_int_hd_handler) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (1);
}
