/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_brackets.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:03:47 by nrea              #+#    #+#             */
/*   Updated: 2024/04/10 18:16:03 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

/*delete the last token of a stack*/
static void	ft_delete_last(t_token **stack)
{
	t_token	*node;
	t_token	*prev;

	node = NULL;
	prev = NULL;
	node = *stack;
	while (node->next)
	{
		prev = node;
		node = node->next;
	}
	if (prev)
		prev->next = NULL;
	ft_free_token(&node);
}

/*delete the first token of a stack*/

static void	ft_delete_first(t_token **stack)
{
	t_token	*node;

	node = *stack;
	*stack = (*stack)->next;
	ft_free_token(&node);
	(*stack)->prev = NULL;
}

/*strips the outer parenthesis token of a stack and returns the stack*/
t_token	**ft_strip_bracket(t_token **stack)
{
	t_token	*first_token;
	t_token	*last_token;

	if (!*stack)
		return (NULL);
	first_token = NULL;
	last_token = NULL;
	first_token = ft_get_token(*stack, 0);
	last_token = ft_get_token(*stack, -1);
	if (!first_token || !last_token)
	{
		kill_stack(stack);
		return (NULL);
	}
	ft_delete_first(stack);
	if (ft_stack_size(*stack) == 1)
	{
		ft_delete_last(stack);
		return (NULL);
	}
	ft_delete_last(stack);
	return (stack);
}
