/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:04:09 by nrea              #+#    #+#             */
/*   Updated: 2024/03/29 15:12:42 by nrea             ###   ########.fr       */
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

/*Create an array oof pipes int[2] by counting the nb of pipes
needed and allocate the array at the right size
*/
int	p_al(t_node *node, t_shell *shell)
{
	int	pipes_nb;
	int	i;

	pipes_nb = ft_count_pipes(node);
	shell->p_ar.pipes_nb = pipes_nb;
	shell->p_ar.pipes = (int **) malloc(pipes_nb * sizeof(int *));
	if (shell->p_ar.pipes == NULL)
	{
		shell->p_ar.pipes_nb = 0;
		return (-1);
	}
	i = 0;
	while (i < pipes_nb)
	{
		shell->p_ar.pipes[i] = malloc (2 * sizeof (int));
		if (!shell->p_ar.pipes[i])
			return (ft_free_p_ar(shell->p_ar.pipes, i));
		i++;
	}
	return (0);
}

/*initialize all the pipes in the array
returns -1 in case of failure*/
int	init_p(int **p_ar, int pipes_nb)
{
	int	i;

	i = 0;
	while (i < pipes_nb)
	{
		if (pipe(p_ar[i]) == -1)
			ft_close_p_ar(p_ar, i);
		i++;
	}
	return (1);
}

void	ft_close_p_ar(int **p_ar, int pipes_nb)
{
	int	i;

	i = 0;
	if (!pipes_nb)
		return ;
	while (i < pipes_nb)
	{
		close(p_ar[i][0]);
		close(p_ar[i][1]);
		i++;
	}
}

int	ft_free_p_ar(int	**p_ar, int pipes_nb)
{
	int	i;

	i = 0;
	while (i < pipes_nb)
	{
		free(p_ar[i]);
		i++;
	}
	if (pipes_nb)
		free(p_ar);
	p_ar = NULL;
	return (1);
}
