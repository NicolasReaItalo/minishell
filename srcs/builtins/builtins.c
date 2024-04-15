/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:19:29 by nrea              #+#    #+#             */
/*   Updated: 2024/04/15 15:42:40 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

/*
Displays error msg in case of internal error*/
static int	ft_builtin_exit_err(int status, char *cmd)
{
	if (status == 1)
		ft_display_error_msg(cmd, "Internal Error");
	return (status);
}

static	int	save_fds(t_node *node)
{
	if (!node || node->type != N_EXEC)
		return (-1);
	node->stdin = dup(STDIN_FILENO);
	if (node->stdin == -1)
		return (-1);
	node->stdout = dup(STDOUT_FILENO);
	if (node->stdout == -1)
		return (-1);
	return (1);
}

static	int	restore_fds(t_node *node, int pipe_lvl)
{
	if (!node || node->type != N_EXEC)
		return (-1);
	if (pipe_lvl == -1)
	{
		if (dup2(node->stdin, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
		if (dup2(node->stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (-1);
		}
	}
	else
	{
		close(node->stdin);
		close(node->stdout);
	}
	return (1);
}

/*Execute a builtin command thus not using execve.
When executed in the main ( pipe_level == -1 ) we
need to restore the files descriptors afterwards.
 */
int	ft_exec_builtin(t_node *node, int pipe_lvl, t_shell *shell)
{
	t_builtin	f;
	int			exit_status;

	if (save_fds(node) == -1)
		ft_builtin_exit_err(1, NULL);
	if (pipe_lvl != -1)
	{
		if (!shell->p_ar.pipes || !shell->p_ar.pipes)
			ft_builtin_exit_err(1, NULL);
		if (ft_apply_pipe_redir(node, pipe_lvl, shell) == -1)
			return (1);
	}
	if (ft_apply_redir(node) == -1)
		return (1);
	if (node->cmd == NULL)
		return (0);
	f = ft_getbuiltin(node->cmd->content);
	if (!f)
		ft_builtin_exit_err(1, node->cmd->content);
	exit_status = f(node->cmd, node, shell);
	if (restore_fds(node, pipe_lvl) == -1)
		return (-1);
	return (exit_status);
}
