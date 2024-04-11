/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:42:02 by nrea              #+#    #+#             */
/*   Updated: 2024/04/11 18:52:12 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

/*Split the stack into two substacks l and r around the pivot token and
 destroys the pivot token*/
int	split_token_lst(int rank, t_token **st, t_token **l, t_token **r)
{
	t_token	*pivot;
	t_token	*next_token;
	t_token	*prev_token;

	if (!ft_stack_size(*st) || rank < 0 || rank >= ft_stack_size(*st))
		return (-1);
	pivot = ft_get_token(*st, rank);
	next_token = pivot->next;
	if (next_token)
		next_token->prev = NULL;
	ft_free_token(&pivot);
	if (rank != 0)
	{
		prev_token = ft_get_token(*st, rank - 1);
		prev_token->next = NULL;
		*r = *st;
		*l = next_token;
	}
	else
	{
		*r = NULL;
		*l = next_token;
	}
	*st = NULL;
	return (0);
}
