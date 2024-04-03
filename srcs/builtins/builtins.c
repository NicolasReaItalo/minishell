/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:19:29 by nrea              #+#    #+#             */
/*   Updated: 2024/04/03 17:17:46 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	dummy(t_token *cmd, t_shell *shell)
{
	(void) cmd;
	(void) shell;
	return (0);
}

int	ft_is_builtin(t_node *node)
{
	char	*cmd;

	if (!node || node->type != N_EXEC || !node->cmd)
		return (0);
	cmd = node->cmd->content;
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*return a function pointer to the builtin*/
builtin	ft_getbuiltin(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (!ft_strcmp(cmd, "echo"))
		return ((builtin) echo);
	else if (!ft_strcmp(cmd, "cd"))
		return ((builtin) dummy);
	else if (!ft_strcmp(cmd, "export"))
		return ((builtin) dummy);
	else if (!ft_strcmp(cmd, "unset"))
		return ((builtin) dummy);
	else if (!ft_strcmp(cmd, "pwd"))
		return ((builtin) pwd);
	else if (!ft_strcmp(cmd, "env"))
		return ((builtin) env);
	else if (!ft_strcmp(cmd, "exit"))
		return ((builtin) dummy);
	else
		return (NULL);
}

/*
Displays error msg in case of internal error*/
static int	ft_builtin_exit_err(int status, char *cmd)
{
	if (status == 1)
		ft_display_error_msg(cmd, "Internal Error");
	return (status);
}

/*Execute a builtin command thus not using execve.
When executed in the main ( pipe_level == -1 ) we
need to restore the files descriptors afterwards.
 */
int	ft_exec_builtin(t_node *node, int pipe_lvl, t_shell *shell)
{
	builtin	f;
	int		exit_status;

	if (pipe_lvl != -1)
	{
		if (!shell->p_ar.pipes || shell->p_ar.pipes == NULL)
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
	exit_status = f(node->cmd, shell);
	if (pipe_lvl == -1)
	{
		dup2(0, STDIN_FILENO);
		dup2(1, STDOUT_FILENO);
	}
	return (exit_status);
}
