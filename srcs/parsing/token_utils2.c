/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:41:29 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/16 18:02:40 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// Check if it's a whitespace
int	is_wspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&'
		|| c == '(' || c == ')' || c == '\\' || c == ';');
}

void	kill_stack(t_token **stack)
{
	t_token	*tmp;

	while (*stack)
	{
		free((*stack)->content);
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp);
	}
}

// Create a new node
t_token	*new_token(char *str, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_token));
	new->content = ft_substr(str, 0, len);
	if (!(new->content))
		return (free(new), NULL);
	return (new);
}

// Add front
t_token	*add_token(t_token *stack, t_token *new)
{
	if (!stack)
		return (new);
	else if (!new)
		return (stack);
	else
	{
		new->next = stack;
		stack = new;
		new->next->prev = new;
	}
	return (stack);
}
