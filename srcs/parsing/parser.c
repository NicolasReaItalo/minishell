/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:06:14 by nrea              #+#    #+#             */
/*   Updated: 2024/03/08 16:19:51 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TODO
//
//
//
//  ft_exec_node(t_token *stack) |dispatchtokens | display tree | free_tree
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



// void	*ft_set_error(int *error, int type, t_token **right, t_token **left)
// {
// 		if (!*error)
// 			*error = type;
// 		kill_stack(left);
// 		kill_stack(right);
// 		return (NULL);
// }

// /*returns the type && or || of the token gib=ven by rank*/
// int	ft_get_cond_type(t_token *stack, int rank)
// {
// 	t_token *tok;

// 	tok = ft_get_token(stack, rank);
// 	if (!tok && tok->type == OR)
// 		return (N_OR);
// 	else
// 		return (N_AND);
// }


// t_node *ft_conditional_op(t_token **stack, int op_rank, int *error)
// {
// 	t_node	*node;
// 	t_token	*left;
// 	t_token	*right;
// 	node = NULL;
// 	left = NULL;
// 	right = NULL;
// 	node = malloc(sizeof(t_node));
// 	if (!node)
// 	{
// 		kill_stack(stack);
// 		return (ft_set_error(error, 5, NULL, NULL));  // 5 MALLOC ERROR
// 	}
// 	node->type = ft_get_cond_type(*stack, op_rank);
// 	ft_split_token_list(op_rank, stack, &left, &right);
// 	node->left = ft_parser(left, error, 2);
// 	node->right = ft_parser(right, error, 2);
// 	if (!node->left || !node->right)
// 	{
// 		free(node);
// 		return (ft_set_error(error, node->type, &right, &left));
// 	}
// 	return (node);
// }


// t_node * ft_pipe_op(t_token **stack,int op_rank,int *error)
// {
// 	t_node	*node;
// 	t_token	*left;
// 	t_token	*right;

// 	node = NULL;
// 	left = NULL;
// 	right = NULL;
// 	node = malloc(sizeof(t_node));
// 	if (!node)
// 	{
// 		kill_stack(stack);
// 		return (ft_set_error(error, 5, NULL, NULL));  // 5 MALLOC ERROR
// 	}
// 	node->type = N_PIPE;
// 	ft_split_token_list(op_rank, stack, left, right);
// 	node->left = ft_parser(left, error, 1);
// 	node->right = ft_parser(right, error, 1);
// 	if (!node->left || !node->right)
// 	{
// 		free(node);
// 		return (ft_set_error(error, node->type, &right, &left));
// 	}
// 	return (node);
// }


// t_node * ft_exec_node(t_token *stack)
// {

// 	t_node	*node;
// 	node = NULL;
// 	node = malloc(sizeof(t_node));
// 	if (!node)
// 	{
// 		kill_stack(stack);
// 		return (NULL);
// 	}
// 	node->type = N_EXEC;
// 	ft_dispatch_stacks  /// a ecrire, ajouter la fonction de verification
// 	/*
// 	node.type = N_EXEC
// 	parser la stack pour repartir les token entre redir et cmd
// 	verifier la question de l'alternance op cmd ?
// 	return (node);
// 	*/
// }





// /*
// Parse a stack and returns a parsetree t_node* object
// or NULL if the stack is empty or in case of error;
// In case of error the error* argument is set to the corresponding error code
// */
// t_node	*ft_parser(t_token **stack, int *error, int priority)
// {
// 	int		op_rank;

// 	if (!stack)
// 		return (NULL);
// 	if (!priority) /// Si la priority = 0
// 	{
// 		if (ft_check_outer_brackets(*stack)) // est-ce -que la stack estentouree de parenthese
// 			return (ft_parser(ft_strip_bracket(stack), error, 2)); // on relance le parser avec une stack sans ses parentheses
// 		else
// 			return (ft_exec_node(stack)); // BASE CASE on cree un node exec
// 	}
// 	op_rank = -2;
// 	op_rank = ft_find_operator(priority, *stack);
// 	if (op_rank == -1) // Il n'a pas trouve de token avec la priorite recherchee
// 		return (ft_parser(stack, error, priority - 1)); // on reessaye avec une priorite + basse
// 	if (priority == 2)
// 		return (ft_conditional_op(stack, op_rank, error)); /// cree un node condition split la stack right= ft
// 	if (priority == 1)
// 		return (ft_pipe_op(stack, op_rank, error)); /// cree un node pipe split la stack right= ft
// 	return (NULL);
// }

// 	codes d'erreurs :
// 	// 1 : erreur de pipe
// 	// 2 : erreur de or
// 	// 3 : erreur de and
// 	// 4 : erreur de parenthese
// 	// 5 : erreur de malloc
// char	*ft_handle_error(int error)
// {

// 	if (error == 1)
// 		return ("near '|'");
// 	else if (error == 2)
// 		return ("near '&&'");
// 	else if (error == 3)
// 		return ("near '||'");
// 	else if (error == 4)
// 		return ("near '('");
// 	else if (error == 5)
// 		return ("malloc issue");
// 	return ("");
// }










//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
											//	TESTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///test du parser
// int main()
// {

// 	t_node *tree;
// 	int		error;
// 	t_token	*stack;

// 	stack = NULL;
// 	tree  = NULL;

// 	error = 0;
// 	tree = ft_parser(stack, &error, 2);
// 	if (error)
// 	{
// 		printf("parsing error : '%s'\n", ft_handle_error(error));
// 		kill_stack(stack);
// 		ft_free_tree(tree);
// 		return (1);
// 	}
// 	ft_display_tree(tree);
// 	ft_free_tree(tree);
// }


