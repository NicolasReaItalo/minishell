/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:27:07 by nrea              #+#    #+#             */
/*   Updated: 2024/04/10 17:26:37 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

volatile	sig_atomic_t	g_sig;

void sig_int_interactive_handler(int signum)
{
	g_sig = signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

/*set the signals interception for the interactive mode*/
int	set_interactive_signals(void)
{
	g_sig = 0;
	// ajouter termios

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
	return (1);
}

void sig_exec_handler(int signum)
{
	g_sig = signum;
	printf("\n");
}



/*Signals detection when a command process is running*/
int	set_exec_signals(void)
{
	g_sig = 0;
	// ajouter termios

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


void sig_int_hd_handler(int signum)
{
	(void) signum;
	exit(130);
}


int	set_hd_parent_signals(void)
{
	g_sig = 0;
	// ajouter termios

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
	// ajouter termios

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
