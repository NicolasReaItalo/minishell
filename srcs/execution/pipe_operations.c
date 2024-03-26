/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:04:09 by nrea              #+#    #+#             */
/*   Updated: 2024/03/26 13:39:04 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//parcours node.left en comptant le nobre de pipes
int	ft_count_pipes(t_node *node)
{
	if (node->type == N_PIPE)
		return (1 + ft_count_pipes(node->left));
	return (0);
}

int	ft_create_pipe_ar(t_node *node, t_shell *shell)
{
	int	pipes_nb;
	int	i;

	pipes_nb = ft_count_pipes(node);
	shell->pipe_ar.pipes_nb = pipes_nb;
	shell->pipe_ar.pipes = (int **) malloc(pipes_nb * sizeof(int *));
	if (!shell->pipe_ar.pipes)
		return (-1);
	i = 0;
	while (i < pipes_nb)
	{
		shell->pipe_ar.pipes[i] = malloc (2 * sizeof (int));
		if (!shell->pipe_ar.pipes[i])
			return (ft_free_pipe_ar(shell->pipe_ar.pipes, i));
		i++;
	}
	return (0);
}

int	ft_init_pipe_ar(int **pipe_ar, int pipes_nb)
{
	int	i;

	i = 0;
	while (i < pipes_nb)
	{
		if (pipe(pipe_ar[i]) == -1)
			ft_close_pipe_ar(pipe_ar, i);
		i++;
	}
	return (1);
}

void	ft_close_pipe_ar(int **pipe_ar, int pipes_nb)
{
	int	i;

	i = 0;
	while (i < pipes_nb)
	{
		close(pipe_ar[i][0]);
		close(pipe_ar[i][1]);
		i++;
	}
}

int	ft_free_pipe_ar(int	**pipe_ar, int pipes_nb)
{
	int	i;

	i = 0;
	while (i < pipes_nb)
	{
		free(pipe_ar[i]);
		i++;
	}
	if (pipes_nb)
		free(pipe_ar);
	return (1);
}
