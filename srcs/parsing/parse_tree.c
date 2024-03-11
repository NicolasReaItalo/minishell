/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:06:14 by nrea              #+#    #+#             */
/*   Updated: 2024/03/11 14:53:37 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_free_tree(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->type == 0)
	{
		kill_stack(&tree->redir);
		kill_stack(&tree->cmd);
		free(tree);
		return ;
	}
	else
	{
		ft_free_tree(tree->left);
		ft_free_tree(tree->right);
		free(tree);
	}
}

/*	codes d'erreurs :
	1 : erreur de pipe
	2 : erreur de or
	3 : erreur de and
	4 : erreur de parenthese
	5 : erreur de malloc */
char	*ft_handle_tree_error(int error)
{
	if (error == N_PIPE)
		return ("near '|'");
	else if (error == N_OR)
		return ("near '||'");
	else if (error == N_AND)
		return ("near '&&'");
	else if (error == 4)
		return ("near '('");
	else if (error == 5)
		return ("malloc issue");
	return ("");
}

void	*ft_set_tree_error(int *error, int type, t_node *node)
{
	if (!*error)
		*error = type;
	if (!node)
		return (NULL);
	if (node->left)
		ft_free_tree(node->left);
	free(node);
	return (NULL);
}

/*
Parse a stack and returns a parsetree t_node* object
or NULL if the stack is empty or in case of error;
In case of error the error* argument is set to the corresponding error code
*/
t_node	*ft_create_tree(t_token **stack, int *error, int priority)
{
	int		op_rank;

	if (!*stack)
		return (NULL);
	if (!priority)
	{
		if (ft_check_outer_brackets(*stack))
			return (ft_create_tree(ft_strip_bracket(stack), error, 2));
		else
			return (ft_create_exec_node(stack));
	}
	op_rank = -2;
	op_rank = ft_find_operator(priority, *stack);
	if (op_rank == -1)
		return (ft_create_tree(stack, error, priority - 1));
	if (priority == 2)
		return (ft_create_cond_node(stack, op_rank, error));
	if (priority == 1)
		return (ft_create_pipe_node(stack, op_rank, error));
	return (NULL);
}
