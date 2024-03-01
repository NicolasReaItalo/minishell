/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:44:58 by nrea              #+#    #+#             */
/*   Updated: 2024/03/01 16:48:23 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*Returns a pointer to the token at rank
if rank = -1 returns the last token*/
t_token	*ft_get_token(t_token *stack, int rank)
{
	if (rank < -1)
		return (NULL);
	if (rank == -1)
	{
		while (stack->next)
			stack = stack->next;
		return (stack);
	}
	while (rank)
	{
		if (!stack)
			return (NULL);
		stack = stack->next;
		rank--;
	}
	return (stack);
}

int	test_ft_add_token(t_token **stack, char *content, int type)
{
	t_token	*node;

	node = NULL;
	node = malloc (sizeof(t_token));
	if (!node)
		return (-1);
	node->content = ft_strdup(content);
	node->type = type;
	node->next = *stack;
	*stack = node;
	return (0);
}

void	*ft_free_stack(t_token **stack)
{
	t_token	*node;
	t_token	*prev;

	if (!*stack || !stack)
		return (NULL);
	node = *stack;
	while (node)
	{
		prev = node;
		node = node->next;
		free(prev->content);
		free(prev);
	}
	*stack = NULL;
	return (NULL);
}

void	ft_display_stack(t_token *stack)
{
	t_token	*node;
	int		rank;

	rank = 0;
	node = stack;
	if (!node)
		printf("[NULL]\n");
	while (node)
	{
		printf("[%d][%s]\n", rank, node->content);
		node = node->next;
		rank++;
	}
}

/*Returns the size (node numbers) of a stack*/
int	ft_stack_size(t_token *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

int	ft_free_token(t_token **token)
{
	if (!(*token))
		return (0);
	if ((*token)->content)
		free((*token)->content);
	free(*token);
	*token = NULL;
	return (0);
}

void	ft_reverse_stack(t_token **stack)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	if (!*stack || ft_stack_size(*stack) == 1)
		return ;
	current = NULL;
	prev = NULL;
	next = NULL;
	current = *stack;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*stack = prev;
}
