/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/10 10:27:39 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

void exit_gracefully(t_shell *shell, int exit_status)
{
	ft_dprintf(2, "Exiting Minishell... See you soon!\n");
	ft_free_shell(shell);
	exit (exit_status);
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;


	if (set_signals() == -1)
		exit(1);


	(void) argc;
	(void) argv;
	if (!ft_init_shell(&shell, envp))
		return (1);
	shell.get_readline = 1; /////////A supprimer
	repl(&shell);
	exit_gracefully(&shell, 0);
}
