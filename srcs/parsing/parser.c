/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:06:14 by nrea              #+#    #+#             */
/*   Updated: 2024/03/08 17:45:54 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

void	*ft_set_error(int *error, int type, t_token **right, t_token **left)
{
		if (!*error)
			*error = type;
		kill_stack(left);
		kill_stack(right);
		return (NULL);
}

/*returns the type && or || of the token given by rank*/
int	ft_get_cond_type(t_token *stack, int rank)
{
	t_token *tok;

	tok = ft_get_token(stack, rank);
	if (!tok && tok->type == OR)
		return (N_OR);
	else
		return (N_AND);
}


t_node *ft_create_cond_node(t_token **stack, int op_rank, int *error)
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
		return (ft_set_error(error, 5, NULL, NULL));  // 5 MALLOC ERROR
	}
	node->type = ft_get_cond_type(*stack, op_rank);
	ft_split_token_list(op_rank, stack, &left, &right);
	node->left = ft_parse_tree(&left, error, 2);
	node->right = ft_parse_tree(&right, error, 1); ///////voir si opti marche
	if (!node->left || !node->right)
	{
		free(node);
		return (ft_set_error(error, node->type, &right, &left));
	}
	return (node);
}


t_node * ft_create_pipe_node(t_token **stack,int op_rank,int *error)
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
		return (ft_set_error(error, 5, NULL, NULL));  // 5 MALLOC ERROR
	}
	node->type = N_PIPE;
	ft_split_token_list(op_rank, stack, &left, &right);
	node->left = ft_parse_tree(&left, error, 1);
	node->right = ft_parse_tree(&right, error, 0); ///////voir si opti marche
	if (!node->left || !node->right)
	{
		free(node);
		return (ft_set_error(error, node->type, &right, &left));
	}
	return (node);
}


void	ft_token_add_front(t_token**lst, t_token *new)
{
	if (!new)
		return ;
	new->next = *lst;
	new->prev = NULL;
	if (*lst)
		(*lst)->prev = new;
	*lst = new;
}

/*Dispatchs the tokens of the stack between redir(< > << >>) and cmd (WORD)
the stack strts at the last token so we append at front !
*/
void	ft_dispatch_tokens(t_token *stack, t_token *redir, t_token *cmd)
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
			ft_token_add_front(&redir, tok);
		else
			ft_token_add_front(&cmd, tok);
		tok = next;
	}
}


t_node * ft_create_exec_node(t_token **stack)
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
	ft_dispatch_tokens(*stack, node->redir, node->cmd);
	return (node);
}

/*
Parse a stack and returns a parsetree t_node* object
or NULL if the stack is empty or in case of error;
In case of error the error* argument is set to the corresponding error code
*/
t_node	*ft_parse_tree(t_token **stack, int *error, int priority)
{
	int		op_rank;

	if (!stack)
		return (NULL);
	if (!priority) /// Si la priority = 0
	{
		if (ft_check_outer_brackets(*stack)) // est-ce -que la stack estentouree de parenthese ?
			return (ft_parse_tree(ft_strip_bracket(stack), error, 2)); // SI OUI on relance le parser avec une stack sans ses parentheses
		else
			return (ft_create_exec_node(stack)); // BASE CASE on cree un node exec
	}
	op_rank = -2;
	op_rank = ft_find_operator(priority, *stack);
	if (op_rank == -1) // Il n'a pas trouve de token avec la priorite recherchee
		return (ft_parse_tree(stack, error, priority - 1)); // on reessaye avec une priorite + basse
	else
	{
		if (priority == 2)
			return (ft_create_cond_node(stack, op_rank, error)); /// cree un node condition split la stack
		if (priority == 1)
			return (ft_create_pipe_node(stack, op_rank, error)); /// cree un node pipe split la stack
	}
	return (NULL);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
												// TESTS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// /test du parser

///cc -Wall -Wextra  -o test_parse_tree  ./srcs/parsing/*.c -I ./include -I./libft -L./libft  -lft -lreadline
///

#include "tests.h"

char *node_type(int type)
{
	if (type == N_EXEC)
		return ("EXEC");
	if (type == N_PIPE)
		return ("|");
	if (type == N_OR)
		return ("||");
	if (type == N_AND)
		return ("&&");
}


// void ft_display_tree(t_node *tree, int level)
// {
// 	if (!tree)
// 		return ;
// 	printf("level [%d] type [%s]\n", level,node_type( tree->type));
// 	if (tree->type == N_EXEC)

// }


int main()
{

	t_node *tree;
	int		error;
	t_token	*stack;

	stack = NULL;
	tree  = NULL;

	error = 0;

	test_ft_add_token_lst(&stack, "ls", WORD);
	test_ft_add_token_lst(&stack, "-l", WORD);
	test_ft_add_token_lst(&stack, "<", R_IN);
	test_ft_add_token_lst(&stack, "&&", AND);
	test_ft_add_token_lst(&stack, "cat", WORD);


	tree = ft_parse_tree(&stack, &error, 2);
	if (error)
	{
		printf("parsing error : '%s'\n", ft_handle_error(error));
		kill_stack(&stack);
		// ft_free_tree(tree);  ////////A ecrire
		return (1);
	}




	// ft_display_tree(tree);  ////////A ecrire
	// ft_free_tree(tree);  ////////A ecrire
}


