/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/11 16:40:48 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


#include "tests.h"

char *ft_handle_token_errors(int error)
{
	if (error == 1)
		return ("Bad alocation");
	if (error == 2 )
		return ("unclosed quotes");
	return ("");
}


int	main(int argc, char **argv, char **envp)
{
	(void)envp;

	t_token	*stack;
	t_node	*tree;
	int		token_error;
	int		syntax_error;
	int		tree_error;


	if ( argc != 2)
		return (1);
	token_error = 0;
	syntax_error = 0;
	tree_error = 0;
	tree = NULL;
	stack = NULL;

	token_error = tokenise(argv[1], &stack);
	if (token_error)
	{
		printf("tokenisation error: %s\n", ft_handle_token_errors(token_error));
		kill_stack(&stack);
		return (1);

	}

	syntax_error = check_syntax(stack);
	if (syntax_error)
	{
		kill_stack(&stack);
		return (2);

	}
	
	ft_redirections(&stack);

	tree = ft_create_tree(&stack,&tree_error, 2);
	if (tree_error)
	{
		ft_handle_tree_error(tree_error);
		ft_free_tree(tree);
		return (3);
	}

	show_tree(tree, 0);
	ft_free_tree(tree);


	return (0);
}
