/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:13:29 by nrea              #+#    #+#             */
/*   Updated: 2024/03/29 13:08:02 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*
An error has occured: malloc, pipe, fork...
we wait for all the child processes
then close all the pipes and free the pipe array.
*/
static int	ft_abort_safe(int pipe_lvl, t_shell *s)
{
	write(2, "Internal Error\n", 16);
	if (pipe_lvl == 0)
	{
		ft_close_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
		ft_free_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
		s->p_ar.pipes_nb = 0;
		while (wait(NULL) != -1)
		{
		}
		ft_set_exit_status(1, &s->shell_vars);
	}
	return (-1);
}

static void	ft_exec_left(t_node *node, int pipe_lvl, t_shell *s)
{
	if (node->left->type == N_PIPE)
		ft_exec_pipe(node->left, pipe_lvl + 1, s);
	else if (node->left->type == N_EXEC)
	{
		///////Ajouter l'expansion et la gestion des builtins
		node->left->side = left;
		ft_exec_binary(node->left, pipe_lvl, s);
	}
}

static void	ft_exec_right(t_node *node, int pipe_lvl, t_shell *s)
{
	///////Ajouter l'expansion et la gestion des builtins
	node->right->side = right;
	ft_exec_binary(node->right, pipe_lvl, s);
}

static void	ft_close_pipes_and_wait(t_shell *s, int pids[2])
{
	int	exit_status;

	exit_status = 0;
	ft_close_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
	ft_free_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
	s->p_ar.pipes_nb = 0;
	waitpid(pids[1], &exit_status, 0);
	while (wait(NULL) != -1)
	{
	}
	ft_set_exit_status(WEXITSTATUS(exit_status), &s->shell_vars);
}

/*The function that execeute a node pipe
opens a pipe (if pipe_level == 0, allocate the nb of pipes needed)
execute the cmd to the right and the left at the same time in forked
processes but if the left is a pipe stays in the same process.
return 1 in case of success or -1 in case of error (malloc, pipe or fork issue)

*/
int	ft_exec_pipe(t_node *n, int pipe_lvl, t_shell *s)
{
	int	pids[2];

	if (pipe_lvl == 0)
		if (p_ar(n, s) == -1 || init_p(s->p_ar.pipes, s->p_ar.pipes_nb) == -1)
			ft_abort_safe(pipe_lvl, s);
	if (n->left->type == N_EXEC)
	{
		pids[0] = fork();
		if (pids[0] == -1)
			ft_abort_safe(pipe_lvl, s);
		if (pids[0] == 0)
			ft_exec_left(n, pipe_lvl, s);
	}
	else
		ft_exec_left(n, pipe_lvl, s);
	pids[1] = fork();
	if (pids[1] == -1)
		ft_abort_safe(pipe_lvl, s);
	if (pids[1] == 0)
		ft_exec_right(n, pipe_lvl, s);
	if (pipe_lvl == 0)
		ft_close_pipes_and_wait(s, pids);
	return (1);
}
