/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_root.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:31:47 by nrea              #+#    #+#             */
/*   Updated: 2024/04/11 18:29:23 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

static int	status_set(int exit_status)
{
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		return (130);
	}
	else if (g_sig == SIGQUIT)
	{
		g_sig = 0;
		return (131);
	}
	else
		return (WEXITSTATUS(exit_status));
}

/*execute a node exec in a child process and return the exit status
returns -1 in case of failure*/
static int	ft_exec_in_fork(t_node *node, int pipe_nb, t_shell *shell)
{
	int	exit_status;
	int	pid;

	if (set_exec_signals() == -1)
		return (-1);
	exit_status = 0;
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		ft_exec_binary(node, pipe_nb, shell);
	waitpid(pid, &exit_status, 0);
	exit_status = status_set(exit_status);
	if (set_interactive_signals() == -1)
		return (-1);
	return (exit_status);
}

/*Execution of a  and/or node*/
static void	ft_exec_and_or(t_node *tree_root, t_shell *shell)
{
	if (tree_root->type == N_AND)
	{
		ft_exec_root(tree_root->left, shell);
		if (ft_get_exit_status(&shell->shell_vars) == 0)
			ft_exec_root(tree_root->right, shell);
	}
	else if (tree_root->type == N_OR)
	{
		ft_exec_root(tree_root->left, shell);
		if (ft_get_exit_status(&shell->shell_vars) != 0)
			ft_exec_root(tree_root->right, shell);
	}
}

/*Execution of a  exec node
we determine first if it calls a builtin or a binary commmand
if builtin: execution in main process
if binary : child process creatio and execve
in both cases, redirections are applied*/
static int	ft_n_exec(t_node *tree_root, t_shell *shell)
{
	int	exit_status;

	//expansions du node a ajouter
	if (ft_is_builtin(tree_root))
	{
		exit_status = ft_exec_builtin(tree_root, -1, shell);
		ft_set_exit_status(exit_status, &shell->shell_vars);
	}
	else
	{
		exit_status = ft_exec_in_fork(tree_root, -1, shell);
		if (exit_status == -1)
		{
			write(2, "Internal Error\n", 16);
			ft_set_exit_status(1, &shell->shell_vars);
			return (-1);
		}
		ft_set_exit_status(exit_status, &shell->shell_vars);
	}
	return (1);
}

/*The base execution function called at the root of the parse tree*/
int	ft_exec_root(t_node *tree_root, t_shell *shell)
{
	if (!tree_root || !shell)
		return (-1);
	if (tree_root->type == N_EXEC)
		return (ft_n_exec(tree_root, shell));
	else if (tree_root->type == N_PIPE)
	{
		if (set_exec_signals() == -1)
			return (-1);
		if (ft_exec_pipe(tree_root, 0, shell) == -1)
			return (-1);
	}
	else
		ft_exec_and_or(tree_root, shell);
	return (1);
}
