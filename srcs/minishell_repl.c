/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_repl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:39:35 by nrea              #+#    #+#             */
/*   Updated: 2024/04/23 10:47:43 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*set the appropriate status in case of sigint or siguit*/
void	sig_set_status(t_shell *shell)
{
	if (g_sig)
	{
		if (g_sig == SIGINT)
			ft_set_exit_status(g_sig + 128, &shell->shell_vars);
		else
			g_sig = 0;
	}
}

static void	prompt(char **line, t_shell *shell)
{
	if (ft_get_exit_status(&shell->shell_vars))
		*line = readline(ERR_PROMPT);
	else
		*line = readline(OK_PROMPT);
}

/*The main Read Execute Print Loop*/
void	repl(t_shell *shell)
{
	t_token	*stack;
	char	*line;

	while (1)
	{
		stack = NULL;
		line = NULL;
		prompt(&line, shell);
		sig_set_status(shell);
		if (!line)
			exit_gracefully(shell, 0);
		if (ft_strlen(line))
		{
			add_history(line);
			if (evaluate(line, &stack, shell) == -1)
				continue ;
			if (ft_exec_root(shell->tree, shell) == -1)
				return ;
			ft_free_tree(&shell->tree);
		}
		else
			free(line);
	}
}
