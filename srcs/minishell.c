/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/20 14:50:39 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

char	*ft_handle_token_errors(int error)
{
	if (error == 1)
		return ("Bad allocation");
	if (error == 2)
		return ("unclosed quotes");
	if (error == 3)
		return ("Empty string");
	return ("");
}

int	ft_init_shell(t_shell *shell, char **envp)
{
	if (!ft_init_env_vars(shell->env_vars, &shell->shell_vars))
	{
		ft_dprintf(2, "Error during environement variables initialisation\n");
		return (0);
	}
	shell->tree = NULL;
	*shell->pipe_array.pipes = NULL;
	shell->pipe_array.nb_of_pipes = 0;
	ft_fetch_env_vars(shell->env_vars, envp);
	return (1);
}


void	ft_free_shell(t_shell *shell)
{
	ft_free_env_vars(shell->env_vars, &shell->shell_vars);
	ft_free_tree(shell->tree);
	//ajouter une fonction pour free le pipe array
}



int	main(int argc, char **argv, char **envp)
{
	t_token	*stack;
	t_shell	shell;


	int		token_error;
	int		syntax_error;
	int		tree_error;

	(void)envp;
	if (argc != 2)
		return (1);
	token_error = 0;
	syntax_error = 0;
	tree_error = 0;
	stack = NULL;

	if (!ft_init_shell(&shell, envp))
		return(1);
	printf("\n =============== PARSING ===============\n");
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
	shell.tree = ft_create_tree(&stack, &tree_error, 2);
	if (tree_error)
	{
		ft_handle_tree_error(tree_error);
		ft_free_tree(shell.tree);
		return (3);
	}
	show_tree(shell.tree, 0);
	printf("\n =============== EXECUTION ===============\n");

	ft_exec_root(shell.tree, &shell);
	// char **cmd;

	// cmd = NULL;
	// ft_token_to_array(&shell.tree->cmd, &cmd);
	ft_free_shell(&shell);
	return (0);
}
