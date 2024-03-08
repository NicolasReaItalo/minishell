/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:42:02 by nrea              #+#    #+#             */
/*   Updated: 2024/03/08 16:04:02 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*Split the stack into two substacks l and r around the pivot token and
 destroys the pivot token*/
int	ft_split_token_list(int rank, t_token **stack, t_token **l, t_token **r)
{
	t_token	*pivot;
	t_token	*next_token;
	t_token	*prev_token;

	if (!ft_stack_size(*stack) || rank < 0 || rank >= ft_stack_size(*stack))
		return (-1);
	pivot = ft_get_token(*stack, rank);
	next_token = pivot->next;
	if (next_token)
		next_token->prev = NULL;
	ft_free_token(&pivot);
	if (rank != 0)
	{
		prev_token = ft_get_token(*stack, rank - 1);
		prev_token->next = NULL;
		*r = *stack;
		*l = next_token;
	}
	else
	{
		*r = NULL;
		*l = next_token;
	}
	return (0);
}
