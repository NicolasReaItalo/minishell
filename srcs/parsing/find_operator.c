/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:09:49 by nrea              #+#    #+#             */
/*   Updated: 2024/04/10 18:16:15 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

/*loop through the stack and return the rank of the first token of
the desired priority (outside of brackets !).
 Returns -1 if none have been found.
PRIORITY 2 : [&&] [||]
PRIORITY 1:  [|]
PRIORITY 0: [WORD] [(] [)] [<] [<<] [>] [>>] */
int	ft_find_operator(int priority, t_token *stack)
{
	int		in_bracket;
	int		rank;

	in_bracket = 0;
	rank = 0;
	while (stack)
	{
		if (stack->type == O_BRACKET)
			in_bracket++;
		else if (stack->type == C_BRACKET)
			in_bracket--;
		else
		{
			if (priority == 2 && !in_bracket)
				if (stack->type == AND || stack->type == OR)
					return (rank);
			if (priority == 1 && !in_bracket)
				if (stack->type == PIPE)
					return (rank);
		}
		rank++;
		stack = stack->next;
	}
	return (-1);
}
