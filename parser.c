/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:06:14 by nrea              #+#    #+#             */
/*   Updated: 2024/02/29 16:38:57 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


int test_ft_add_token(t_token **stack, char *content, int type) //////A supprimer
{
	t_token *node;

	node = NULL;

	node = malloc (sizeof(t_token));
	if (!node)
	{
		printf ("Erreur de malloc !");
		return (-1);
	}
	node->content = ft_strdup(content);
	node->type = type;
	node->next = *stack;
	*stack = node;
	return (0);
}


void *ft_free_stack(t_token **stack)
{
	t_token *node;
	t_token *prev;

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
	t_token *node;
	int rank;

	rank = 0;
	node = stack;
	if (!node)
		printf("[NULL]\n");
	while (node)
	{
		printf("[%d][%s]\n",rank, node->content);
		node = node->next;
		rank++;
	}

}

/*Returns the size (node numbers) of a stack*/
int	ft_stack_size(t_token *stack)
{
	int count;

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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////




/*loop through the stack and return the rank of the first token of
the desired priority.
Returns -1 if none have been found
PRIORITY 2 : [&&] [||]
PRIORITY 1:  [|]
PRIORITY 0: [WORD] [(] [)] [<] [<<] [>] [>>] */
int	ft_find_operator(int priority, t_token *stack)
{
	int		in_bracket; // flag bracket 0 ou 1
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
			if (priority == 1 && !in_bracket)
				if (stack->type == PIPE)
					return (rank);
		}
		rank++;
		stack = stack->next;
	}
	return (-1);
}



/*Split the stack into two substacks left and right around the pivot token, destroys the token*/
int	ft_split_token_list(int rank, t_token **stack, t_token **left, t_token **right)
{
	t_token	*pivot; // le token a supprimer
	t_token	*next_token; // le token suivant
	t_token	*prev_token; // le token precedent

	pivot = NULL;
	next_token = NULL;
	if (!ft_stack_size(*stack) || rank < 0 || rank >= ft_stack_size(*stack))
		return (-1);
	pivot = ft_get_token(*stack, rank);
	next_token = pivot->next;
		ft_free_token(&pivot);
	if (rank != 0)
	{
		prev_token = ft_get_token(*stack, rank - 1);
		prev_token->next = NULL;
		*right = *stack;
		*left = next_token;
	}
	else
	{
		*right = NULL;
		*left = next_token;
	}
	return (0);
}

/*delete the last token of a stack*/
void	ft_delete_last(t_token **stack)
{
	t_token *node;
	t_token *prev;

	node = NULL;
	prev = NULL;
	node = *stack;
	while (node->next)
	{
		prev = node;
		node = node->next;
	}
	if (prev)
		prev->next = NULL;
	ft_free_token(&node);
}

void	ft_delete_first(t_token **stack)
{
	t_token *node;

	node = NULL;
	node = *stack;
	*stack = (*stack)->next;
	ft_free_token(&node);
}


/*strips the outer parenthesis token of a stack and returns the stack*/
t_token	*ft_strip_bracket(t_token **stack)
{
	t_token	*first_token;
	t_token	*last_token;

	if(!*stack)
		return (NULL);
	first_token = NULL;
	last_token = NULL;
	first_token = ft_get_token(*stack, 0);
	last_token = ft_get_token(*stack, -1);
	if (!first_token || !last_token)
		return (ft_free_stack(stack));
	ft_delete_first(stack);
	if (ft_stack_size(*stack) == 1)
	{
		ft_delete_last(stack);
		return (NULL);
	}
	ft_delete_last(stack);
	return (*stack);
}


void	*ft_set_error(int *error, int type, t_token **right, t_token **left)
{
		if (!*error)
			*error = type;
		ft_free_stack(&left);
		ft_free_stack(&right);
		return (NULL);
}

/*returns the type && or || of the token gib=ven by rank*/
int	ft_get_cond_type(t_token *stack, int rank)
{
	t_token *tok;

	tok = ft_get_token(stack, rank);
	if (!tok && tok->type == OR)
		return (N_OR);
	else
		return (N_AND);
}


ft_conditional_op(t_token **stack, int op_rank, int *error)
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
		ft_free_stack(stack);
		return (ft_set_error(error, 5, NULL, NULL));  // 5 MALLOC ERROR
	}
	node->type = ft_get_cond_type(*stack, op_rank);
	ft_split_token_list(op_rank, stack, left, right);
	node->left = ft_parser(left, error, 2);
	node->right = ft_parser(right, error, 2);
	if (!node->left || !node->right)
	{
		free(node);
		return (ft_set_error(error, node->type, &right, &left));
	}
	return (node);
}


ft_pipe_op(t_token **stack,int op_rank,int *error)
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
		ft_free_stack(stack);
		return (ft_set_error(error, 5, NULL, NULL));  // 5 MALLOC ERROR
	}
	node->type = N_PIPE;
	ft_split_token_list(op_rank, stack, left, right);
	node->left = ft_parser(left, error, 1);
	node->right = ft_parser(right, error, 1);
	if (!node->left || !node->right)
	{
		free(node);
		return (ft_set_error(error, node->type, &right, &left));
	}
	return (node);
}


ft_exec_node(t_token *stack)
{

	t_node	*node;
	node = NULL;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		ft_free_stack(stack);
		return (NULL);
	}
	node->type = N_EXEC;
	ft_dispatch_stacks  /// a ecrire, ajouter la fonction de verification
	/*
	node.type = N_EXEC
	parser la stack pour repartir les token entre redir et cmd
	verifier la question de l'alternance op cmd ?
	return (node);
	*/
}



/*Check if the stack is surronded by parenthesis
  return 1 in case of success or 0 otherwise
*/
int	ft_check_outer_brackets(t_token *stack)
{
	t_token *first;
	t_token *last;

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



/*
Parse a stack and returns a parsetree t_node* object
or NULL if the stack is empty or in case of error;
In case of error the error* argument is set to the corresponding error code
*/
t_node	*ft_parser(t_token **stack, int *error, int priority)
{
	int		op_rank;

	if (!stack)
		return (NULL);
	if (!priority) /// Si la priority = 0
	{
		if (ft_check_outer_brackets(*stack)) // est-ce -que la stack estentouree de parenthese
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
// 		ft_free_stack(stack);
// 		ft_free_tree(tree);
// 		return (1);
// 	}
// 	ft_display_tree(tree);
// 	ft_free_tree(tree);
// }



// /// TEST DE ft_split_token_list
// int main()
// {

// 	t_token	*stack;
// 	t_token	*right;
// 	t_token	*left;

// 	stack = NULL;
// 	right = NULL;
// 	left = NULL;

// 	test_ft_add_token(&stack, "&&", AND);
// 	test_ft_add_token(&stack, "|", PIPE);
// 	test_ft_add_token(&stack, "CMD1", WORD);
// 	test_ft_add_token(&stack, "||", OR);
// 	test_ft_add_token(&stack, "CMD2", WORD);
// 	test_ft_add_token(&stack, "CMD3", WORD);
// 	test_ft_add_token(&stack, "CMD4", WORD);
// 	test_ft_add_token(&stack, "CMD5", WORD);

// printf("##########STACK INITIALE####################\n");
// 	ft_display_stack(stack);
// int retour;
// 	retour = ft_split_token_list(4, &stack, &left, &right);
// printf("Retour de split [%d]\n", retour);
// printf("##########APRES LE SPLIT####################\n");
// printf("#########left\n");
// 	ft_display_stack(left);
// printf("#########right\n");
// 	ft_display_stack(right);

// 	if (retour == -1)
// 		ft_free_stack(&stack);

// 	ft_free_stack(&left);
// 	ft_free_stack(&right);


// 	return (0);
// }





/// TEST DE ft_find_token
// int main()
// {

// 	t_token	*stack;
// 	t_token	*right;
// 	t_token	*left;

// 	stack = NULL;
// 	right = NULL;
// 	left = NULL;

// 	// test_ft_add_token(&stack, "&&", AND);
// 	// test_ft_add_token(&stack, "|", PIPE);
// 	// test_ft_add_token(&stack, "CMD1", WORD);
// 	test_ft_add_token(&stack, "||", OR);
// 	test_ft_add_token(&stack, "CMD2", WORD);
// 	// test_ft_add_token(&stack, "CMD3", WORD);
// 	// test_ft_add_token(&stack, "CMD4", WORD);
// 	// test_ft_add_token(&stack, "CMD5", WORD);

// printf("##########STACK####################\n");
// 	ft_display_stack(stack);
// 	int priority = 2;
// printf("rang du premier token de priorite %d [%d]\n", priority, ft_find_operator(priority,stack));
// 	 priority = 1;
// printf("rang du premier token de priorite %d [%d]\n", priority, ft_find_operator(priority,stack));

// 		ft_free_stack(&stack);


// 	return (0);
// }







// TEST DE ft_check_outer_brackets
// int main()
// {

// 	t_token	*stack;
// 	t_token	*right;
// 	t_token	*left;

// 	stack = NULL;
// 	right = NULL;
// 	left = NULL;

// 	test_ft_add_token(&stack, "&&", AND);
// 	test_ft_add_token(&stack, "|", PIPE);
// 	test_ft_add_token(&stack, "(",O_BRACKET);
// 	test_ft_add_token(&stack, "CMD1", WORD);
// 	test_ft_add_token(&stack, "||", OR);
// 	test_ft_add_token(&stack, ")",C_BRACKET);
// 	test_ft_add_token(&stack, "CMD2", WORD);
// 	test_ft_add_token(&stack, "CMD3", WORD);
// 	test_ft_add_token(&stack, "CMD4", WORD);
// 	test_ft_add_token(&stack, "CMD5", WORD);


// printf("##########STACK ####################\n");
// 	ft_display_stack(stack);


// 	printf("retour de check_outer_brackets [%d] \n", ft_check_outer_brackets(stack) );

// 		ft_free_stack(&stack);

// 	return (0);
// }




// // TEST DE ft_strip_bracket
// int main()
// {

// 	t_token	*stack;
// 	t_token	*right;
// 	t_token	*left;

// 	stack = NULL;
// 	right = NULL;
// 	left = NULL;

// 	test_ft_add_token(&stack, ")",C_BRACKET);
// 	test_ft_add_token(&stack, "&&", AND);
// 	test_ft_add_token(&stack, "|", PIPE);
// 	test_ft_add_token(&stack, "CMD1", WORD);
// 	test_ft_add_token(&stack, "||", OR);
// 	test_ft_add_token(&stack, "CMD2", WORD);
// 	test_ft_add_token(&stack, "CMD3", WORD);
// 	test_ft_add_token(&stack, "CMD4", WORD);
// 	test_ft_add_token(&stack, "CMD5", WORD);
// 	test_ft_add_token(&stack, "(",O_BRACKET);


// printf("##########STACK INITIALE####################\n");
// 	ft_display_stack(stack);

// printf("##########APRES LE STRIP####################\n");
// stack = ft_strip_bracket(&stack);
// 	ft_display_stack(stack);

// 		ft_free_stack(&stack);

// 	return (0);
// }
