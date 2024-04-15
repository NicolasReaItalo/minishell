/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:13:29 by nrea              #+#    #+#             */
/*   Updated: 2024/04/15 13:36:49 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"
#include "word_expansion.h"

static void	ft_exec_left(t_node *node, int pipe_lvl, t_shell *s)
{
	int	exit_status;

	if (node->left->type == N_PIPE)
		ft_exec_pipe(node->left, pipe_lvl + 1, s);
	else if (node->left->type == N_EXEC)
	{
		exit_status = word_expand(node->left, s);
		if (exit_status) // voir codes d'erreur pour quitter si pb malloc
		{
			ft_set_exit_status(exit_status, &s->shell_vars);
			exit (exit_status);
		}
		node->left->side = left;
		if (ft_is_builtin(node->left))
		{
			exit_status = ft_exec_builtin(node->left, pipe_lvl, s);
			ft_free_shell(s);
			exit(exit_status);
		}
		else
			ft_exec_binary(node->left, pipe_lvl, s);
	}
}

static void	ft_exec_right(t_node *node, int pipe_lvl, t_shell *s)
{
	int	exit_status;

	exit_status = word_expand(node->right, s);
	if (exit_status) // voir codes d'erreur pour quitter si pb malloc
	{
		ft_set_exit_status(exit_status, &s->shell_vars);
		exit (exit_status);
	}
	node->right->side = right;
	if (ft_is_builtin(node->right))
	{
		exit_status = ft_exec_builtin(node->right, pipe_lvl, s);
		ft_free_shell(s);
		exit(exit_status);
	}
	else
		ft_exec_binary(node->right, pipe_lvl, s);
}

static void	set_sig_stat(t_shell *s, int exit_status)
{
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		ft_set_exit_status(130, &s->shell_vars);
	}
	else if (g_sig == SIGQUIT)
	{
		g_sig = 0;
		ft_set_exit_status(131, &s->shell_vars);
	}
	else
		ft_set_exit_status(WEXITSTATUS(exit_status), &s->shell_vars);
}

static int	ft_close_pipes_and_wait(int pipe_lvl, t_shell *s, int pids[2])
{
	int	exit_status;

	if (pipe_lvl == 0)
	{
		exit_status = 0;
		if (s->p_ar.pipes_nb != 0)
		{
			ft_close_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
			ft_free_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
			s->p_ar.pipes_nb = 0;
		}
		waitpid(pids[1], &exit_status, 0);
		while (wait(NULL) != -1)
		{
		}
		set_sig_stat(s, exit_status);
		if (set_interactive_signals() == -1)
			return (-1);
	}
	return (1);
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
	{
		if (p_al(n, s) == -1)
			return (ft_pipe_abort_safe(pipe_lvl, s));
		if (init_p(s->p_ar.pipes, s->p_ar.pipes_nb) == -1)
			return (ft_pipe_abort_safe(pipe_lvl, s));
	}
	if (n->left->type == N_EXEC)
	{
		pids[0] = fork();
		if (pids[0] == -1)
			ft_pipe_abort_safe(pipe_lvl, s);
		if (pids[0] == 0)
			ft_exec_left(n, pipe_lvl, s);
	}
	else
		ft_exec_left(n, pipe_lvl, s);
	pids[1] = fork();
	if (pids[1] == -1)
		ft_pipe_abort_safe(pipe_lvl, s);
	if (pids[1] == 0)
		ft_exec_right(n, pipe_lvl, s);
	return (ft_close_pipes_and_wait(pipe_lvl, s, pids));
}
