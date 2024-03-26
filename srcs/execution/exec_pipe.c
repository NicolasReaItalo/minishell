/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:13:29 by nrea              #+#    #+#             */
/*   Updated: 2024/03/26 14:41:27 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*Exit safely the ft_exec function
Displays eror msg in case of internal error or cmd not found*/
static int	ft_pipe_exit_safe(int status, t_shell *shell)
{
	if (status == 1)
		ft_display_error_msg(NULL, "Internal Error");
	if (shell)
		ft_free_shell(shell);
	exit (status);
}

static void	ft_exec_left(t_node *node, int pipe_lvl, t_shell *s)
{
	if (node->left->type == N_PIPE)
		ft_exec_pipe(node->left, pipe_lvl + 1, s);
	else if (node->left->type == N_EXEC)
	{
		node->left->side = left;///////Ajouter l'expansion et la gestion des builtins
		ft_exec(node->left, pipe_lvl, s);
	}
}

static void	ft_exec_right(t_node *node, int pipe_lvl, t_shell *s)
{
	node->right->side = right; ///////Ajouter l'expanion et la gestion des builtins
	ft_exec(node->right, pipe_lvl, s);
}

static void	ft_close_and_free(t_shell *s)
{
	ft_close_pipe_ar(s->pipe_ar.pipes, s->pipe_ar.pipes_nb);
	ft_free_pipe_ar(s->pipe_ar.pipes, s->pipe_ar.pipes_nb);
	ft_free_shell(s);
}

/*The function that execeute a node pipe
opens a pipe (if pipe_level == 0, allocate the nb of pipes needed)
execute the cmd to the right and the left at the same time in forked
processes.
Exit with the exit value of the left command
*/
void	ft_exec_pipe(t_node *node, int pipe_lvl, t_shell *s)
{
	int	exit_status;
	int	pids[2];

	if (pipe_lvl == 0)
	{
		if (ft_create_pipe_ar(node, s) == -1)
			ft_pipe_exit_safe(1, s);
		if (ft_init_pipe_ar(s->pipe_ar.pipes, s->pipe_ar.pipes_nb) == -1)
			ft_pipe_exit_safe(1, s);
	}
	pids[0] = fork();
	if (pids[0] == -1)
		ft_pipe_exit_safe(1, s);
	if (pids[0] == 0)
		ft_exec_left(node, pipe_lvl, s);
	pids[1] = fork();
	if (pids[1] == -1)
		ft_pipe_exit_safe(1, s);
	if (pids[1] == 0)
		ft_exec_right(node, pipe_lvl, s);
	ft_close_and_free(s);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}
