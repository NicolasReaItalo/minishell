/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:04:09 by nrea              #+#    #+#             */
/*   Updated: 2024/03/25 17:42:58 by nrea             ###   ########.fr       */
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

int	ft_create_pipe_array(t_node *node, t_shell *shell)
{
	int	nb_of_pipes;
	int	i;

	nb_of_pipes = ft_count_pipes(node);
	shell->pipe_array.nb_of_pipes = nb_of_pipes;
	shell->pipe_array.pipes = (int **) malloc(nb_of_pipes * sizeof(int *));
	if (!shell->pipe_array.pipes)
		return (-1);
	i = 0;
	while (i < nb_of_pipes)
	{
		shell->pipe_array.pipes[i] = malloc (2 * sizeof (int));
		if (!shell->pipe_array.pipes[i])
			return (ft_free_pipe_array(shell->pipe_array.pipes, i));
		i++;
	}
	return (0);
}

int	ft_initialize_pipe_array(int **pipe_array, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < nb_of_pipes)
	{
		if (pipe(pipe_array[i]) == -1)
			ft_close_pipe_array(pipe_array, i);
		i++;
	}
	return (1);
}

void	ft_close_pipe_array(int **pipe_array, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < nb_of_pipes)
	{
		close(pipe_array[i][0]);
		close(pipe_array[i][1]);
		i++;
	}
}

int	ft_free_pipe_array(int	**pipe_array, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < nb_of_pipes)
	{
		free(pipe_array[i]);
		i++;
	}
	if (nb_of_pipes)
		free(pipe_array);
	return (1);
}
