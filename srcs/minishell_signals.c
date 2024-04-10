/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:27:07 by nrea              #+#    #+#             */
/*   Updated: 2024/04/10 10:34:05 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile	sig_atomic_t	g_sig;

void sig_int_handler(int signum)
{
	g_sig = signum;
	if (g_sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}

}

void sig_quit_handler(int signum)
{
	g_sig = signum;
	rl_on_new_line();
	(void)signum;
	rl_redisplay();
	printf("\033[K");   // Clear from cursor position to end of the line
}

/*set the signals interception for the interactive mode*/
int	set_signals(void)
{
	g_sig = 0;
	// ajouter termios

	if (signal(SIGINT, sig_int_handler) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	if (signal(SIGQUIT, sig_quit_handler) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (1);
}
