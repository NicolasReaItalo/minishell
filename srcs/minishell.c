/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/07 16:39:22 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_sadly(t_shell *shell, int exit_status)
{
	ft_dprintf(2, "\033[1;91mMinishell has exited due to an error\033[0m\n");
	ft_free_shell(shell);
	exit (exit_status);
}

void	exit_gracefully(t_shell *shell, int exit_status)
{
	write(1, "exit\n", 6);
	ft_free_shell(shell);
	exit (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		exit (1);
	if (set_interactive_signals() == -1)
		exit(1);
	if (!ft_init_shell(&shell, envp))
		return (1);
	if (!ft_strlen(ft_get_var_value("PATH", shell.env_vars, shell.shell_vars)))
	{
		ft_dprintf(2, "%s", PATH_MSG);
		if (ft_set_var("PATH", D_PATH, shell.env_vars, &shell.shell_vars) != 1)
		{
			ft_dprintf(2, "PATH init Error\n");
			ft_free_shell(&shell);
			exit(1);
		}
	}
	repl(&shell);
	exit_gracefully(&shell, ft_get_exit_status(&shell.shell_vars));
}
