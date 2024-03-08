/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:50:32 by nrea              #+#    #+#             */
/*   Updated: 2024/03/08 13:54:11 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	test_ft_add_token_front(t_token **stack, char *content, int type)
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

int test_ft_add_token_lst(t_token **stack, char *content, int type)
{
	t_token *new_node;
	t_token *last_node;

	new_node = NULL;
	last_node = NULL;

	new_node = malloc (sizeof(t_token));
	if (!new_node)
		return (-1);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	new_node->type = type;
	if (!*stack)
	{
		new_node->prev = NULL;
		*stack = new_node;
		return (0);
	}
	last_node = *stack;
	while(last_node->next)
		last_node = last_node->next;
	new_node->prev = last_node;
	last_node->next = new_node;
	return (0);
}

//return the type as a str
char	*type(int type)
{
	if (type == 0)
		return ("WORD");
	if (type == 1)
		return ("|");
	if (type == 2)
		return ("&&");
	if (type == 3)
		return ("||");
	if (type == 4)
		return ("<");
	if (type == 5)
		return (">");
	if (type == 6)
		return (">>");
	if (type == 7)
		return ("<<");
	if (type == 8)
		return ("(");
	if (type == 9)
		return (")");
	return ("UNKNOWN");
}

void	ft_display_stack(t_token *stack)
{
	t_token	*node;
	int		rank;

	rank = 0;
	node = ft_get_token(stack, -1);
	if (!node)
		printf("[NULL]\n");
	while (node)
	{
		printf("[%d]	type[%s]	content:[%s]\n", rank,type(node->type), node->content);
		node = node->prev;
		rank++;
	}
}
