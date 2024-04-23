/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:27:07 by nrea              #+#    #+#             */
/*   Updated: 2024/04/23 11:40:02 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig;

void	sig_int_interactive_handler(int signum)
{
	g_sig = signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

/*set the signals interception for the interactive mode*/
int	set_interactive_signals(void)
{
	g_sig = 0;
	if (signal(SIGINT, sig_int_interactive_handler) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (1);
}

void	sig_exec_handler(int signum)
{
	g_sig = signum;
	printf("\n");
}

/*Signals detection when a command process is running*/
int	set_exec_signals(void)
{
	g_sig = 0;
	if (signal(SIGINT, sig_exec_handler) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	if (signal(SIGQUIT, sig_exec_handler) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (1);
}
