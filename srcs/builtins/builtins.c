/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 10:19:29 by nrea              #+#    #+#             */
/*   Updated: 2024/04/04 15:39:13 by nrea             ###   ########.fr       */
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

	if (!node || node->type != N_EXEC || !node->cmd || !node->cmd->content)
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
t_builtin	ft_getbuiltin(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (!ft_strcmp(cmd, "echo"))
		return ((t_builtin) echo);
	else if (!ft_strcmp(cmd, "cd"))
		return ((t_builtin) cd);
	else if (!ft_strcmp(cmd, "export"))
		return ((t_builtin) export);
	else if (!ft_strcmp(cmd, "unset"))
		return ((t_builtin) unset);
	else if (!ft_strcmp(cmd, "pwd"))
		return ((t_builtin) pwd);
	else if (!ft_strcmp(cmd, "env"))
		return ((t_builtin) env);
	else if (!ft_strcmp(cmd, "exit"))
		return ((t_builtin) dummy);
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
	t_builtin	f;
	int			exit_status;

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
