/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:27:07 by nrea              #+#    #+#             */
/*   Updated: 2024/04/10 13:50:17 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

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

void sig_quit__exec_handler(int signum)
{
	g_sig = signum;
}

void sig_int_exec_handler(int signum)
{
	g_sig = signum;
	printf("\n");
}

/*Signals detection when a command process is running*/
int	set_exec_signals(void)
{
	g_sig = 0;
	// ajouter termios

	if (signal(SIGINT, sig_int_exec_handler) == SIG_ERR)
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





void sig_int_hd_handler(int signum)
{
	g_sig = signum;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// printf("\n");
}


/*set the signals interception for the heredoc  mode*/
int	set_hd_signals(void)
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

