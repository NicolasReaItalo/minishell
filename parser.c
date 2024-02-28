/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:06:14 by nrea              #+#    #+#             */
/*   Updated: 2024/02/28 17:43:55 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"




///A inclure dans token.h

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


/*loop through the stack and return the rank of the first token of
the desired priority.
Returns -1 if none have been found
PRIORITY 2 : [&&] [||]
PRIORITY 1:  [|]
PRIORITY 0: [WORD] [(] [)] [<] [<<] [>] [>>] */
int	ft_find_operator(int priority, t_token *stack)
{
	int		in_bracket; // flag bracket -1 ou 1
	int		rank;

	in_bracket = 0;
	rank = 0;
	while(stack)
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
			if (priority == 2 && !in_bracket)
				if (stack->type == PIPE)
					return (rank);
		}
		rank++;
		stack = stack->next;
	}
	return (-1);
}

/*strips the outer parenthesis token of a stack and returns the stack*/
t_token	*ft_strip_bracket(t_token **stack)
{
/*
	recupere le premier node
		verifie qu'il est (
	recupere le dernier node
		verifie qu'il est )
	supprime le premier node
	supprime le dernier node
	retourne la stack
*/
}


ft_conditional_op(t_token **stack, int op_rank, int *error)
{
/*
	token = gettoken(oprank)
	node = malloc(node)
		protection...
	si token.type == AND
		node.type =  N_AND
	else
		node.type = N_OR
	split_left = ft_split_l(stack, op_rank)
	split_right = ft_split_right(stack, op_rank)

	node.left = ft_parser(split_left, error, 2);
	if (!node.left)
	{
		if (error == 0)
			*error = node.type
		free(node);
		free_stack(split_left);
		free_stack(split_right);
		return (NULL);
	}
	node.right = ft_parser(split_right, error, 2);
	if (!node.right)
	{
		if (error == 0)
			*error = node.type
		free(node);
		free_stack(split_left);
		free_stack(split_right);
		return (NULL);
	}
	return (node);
*/
}

ft_pipe_op(t_token **stack,int op_rank,int *error)
{
/*
	node = malloc(node)
		protection...
	node.type = N_PIPE
	split_left = ft_split_l(stack, op_rank)
	split_right = ft_split_r(stack, op_rank)

	node.left = ft_parser(split_left, error, 2);
	if (!node.left)
	{
		if (error == 0)
			*error = node.type
		free(node);
		free_stack(split_left);
		free_stack(split_right);
		return (NULL);
	}
	node.right = ft_parser(split_right, error, 2);
	if (!node.right)
	{
		if (error == 0)
			*error = node.type
		free(node);
		free_stack(split_left);
		free_stack(split_right);
		return (NULL);
	}
	return (node);
*/


}
ft_exec_node(t_token *stack)
{
	/*
	node = malloc(node)
		SI pb malloc
		{
			if (!*error)
				error = MALLOC
				free_stack(stack)
				return (NULL);
		}
	node.type = N_EXEC
	parser la stack pour repartir les token entre redir et cmd
	verifier la question de l'alternance op cmd ?
	return (node);
	*/
}



/*
Parse a stack and returns a parsetree t_node* object
or NULL if the stack is empty or in case of error;
In case of error the error* argument is set to the corresponding error code
*/
t_node	*ft_parser(t_token **stack, int *error, int priority)
{
	t_token	*first_token;
	int		op_rank;

	if (!stack)
		return (NULL);
	first_token = NULL;
	if (!priority) /// Si la priority = 0
	{
		first_token = ft_get_token(*stack,0); // on recupere le premier token
		if (first_token && first_token->type == O_BRACKET) // si le premier token est une parenthese ouvrante
			return (ft_parser(ft_strip_bracket(stack), error, 2)); // on relance le parser avec une stack sans ses parentheses
		else
			return (ft_exec_node(stack)); // BASE CASE on cree un node exec
	}
	op_rank = -2;
	op_rank = ft_find_operator(priority, *stack);
	if (op_rank == -1) // Il n'a pas trouve de token avec la priorite recherchee
		return (ft_parser(stack, error, priority - 1)); // on reessaye avec une priorite + basse
	if (priority == 2)
		return (ft_conditional_op(stack, op_rank, error)); /// cree un node condition split la stack right= ft
	if (priority == 1)
		return (ft_pipe_op(stack, op_rank, error)); /// cree un node pipe split la stack right= ft
	return (NULL);
}

	// codes d'erreurs :
	// 1 : erreur de pipe
	// 2 : erreur de or
	// 3 : erreur de and
	// 4 : erreur de parenthese
	// 5 : erreur de malloc
char	*ft_handle_error(int error)
{

	if (error == 1)
		return ("near '|'");
	else if (error == 2)
		return ("near '&&'");
	else if (error == 3)
		return ("near '||'");
	else if (error == 4)
		return ("near '('");
	else if (error == 5)
		return ("malloc issue");
	return ("");
}



int main()
{

	t_node *tree;
	int		error;
	t_token	*stack;

	stack = NULL;
	tree  = NULL;

	error = 0;
	tree = ft_parser(stack, &error, 2);
	if (error)
	{
		printf("parsing error : '%s'\n", ft_handle_error(error));
		ft_free_stack(stack);
		ft_free_tree(tree);
		return (1);
	}
	ft_display_tree(tree);
}

