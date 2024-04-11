/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_outer_brackets.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:15:37 by nrea              #+#    #+#             */
/*   Updated: 2024/04/10 18:16:03 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

/*Check if the stack is surrounded by parenthesis
  return 1 in case of success or 0 otherwise
*/
int	ft_check_outer_brackets(t_token *stack)
{
	t_token	*first;
	t_token	*last;

	first = NULL;
	last = NULL;
	first = ft_get_token(stack, 0);
	last = ft_get_token(stack, -1);
	if (!first || !last)
		return (0);
	if (first->type != C_BRACKET || last->type != O_BRACKET)
		return (0);
	return (1);
}
