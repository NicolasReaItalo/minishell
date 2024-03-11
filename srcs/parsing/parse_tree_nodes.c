/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:54:45 by nrea              #+#    #+#             */
/*   Updated: 2024/03/11 14:02:32 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*returns the type && or || of the token given by rank*/
int	ft_get_cond_type(t_token *stack, int rank)
{
	t_token	*tok;

	tok = ft_get_token(stack, rank);
	if (tok->type == OR)
		return (N_OR);
	else
		return (N_AND);
}

/*Create a conditional node either && or ||*/
t_node	*ft_create_cond_node(t_token **stack, int op_rank, int *error)
{
	t_node	*node;
	t_token	*left;
	t_token	*right;

	node = NULL;
	left = NULL;
	right = NULL;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		kill_stack(stack);
		return (ft_set_error(error, 5, NULL));
	}
	node->type = ft_get_cond_type(*stack, op_rank);
	ft_split_token_list(op_rank, stack, &left, &right);
	node->left = ft_create_tree(&left, error, 2);
	if (!node->left)
		return (ft_set_error(error, node->type, node));
	node->right = ft_create_tree(&right, error, 1);
	if (!node->right)
		return (ft_set_error(error, node->type, node));
	return (node);
}

/*Create a pipe node*/
t_node	*ft_create_pipe_node(t_token **stack, int op_rank, int *error)
{
	t_node	*node;
	t_token	*left;
	t_token	*right;

	node = NULL;
	left = NULL;
	right = NULL;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		kill_stack(stack);
		return (ft_set_error(error, 5, NULL));
	}
	node->type = N_PIPE;
	ft_split_token_list(op_rank, stack, &left, &right);
	node->left = ft_create_tree(&left, error, 1);
	if (!node->left)
		return (ft_set_error(error, node->type, node));
	node->right = ft_create_tree(&right, error, 0);
	if (!node->right)
		return (ft_set_error(error, node->type, node));
	return (node);
}

/*Dispatchs the tokens of the stack between redir(< > << >>) and cmd (WORD)
the stack strts at the last token so we append at front !
*/
void	ft_dispatch_tokens(t_token *stack, t_token **redir, t_token **cmd)
{
	t_token	*tok;
	t_token	*next;

	next = NULL;
	tok = stack;
	if (!tok)
		return ;
	while (tok)
	{
		next = tok->next;
		if (tok->type >= 4 && tok->type <= 7)
			ft_token_add_front(redir, tok);
		else
			ft_token_add_front(cmd, tok);
		tok = next;
	}
}

/*create an exec node, the leaves of our tree*/
t_node	*ft_create_exec_node(t_token **stack)
{
	t_node	*node;

	node = NULL;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		kill_stack(stack);
		return (NULL);
	}
	node->type = N_EXEC;
	node->redir = NULL;
	node->cmd = NULL;
	node->in = 0;
	node->out = 1;
	node->bultin = 0;
	ft_dispatch_tokens(*stack, &node->redir, &node->cmd);
	return (node);
}
