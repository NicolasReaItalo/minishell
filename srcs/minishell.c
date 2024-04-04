/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/04 11:56:40 by nrea             ###   ########.fr       */
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

void	ft_free_shell(t_shell *shell)
{
	ft_free_env_vars(shell->env_vars, &shell->shell_vars);
	ft_free_tree(shell->tree);
}

int	ft_init_shell(t_shell *shell, char **envp)
{
	if (!ft_init_env_vars(shell->env_vars, &shell->shell_vars))
	{
		ft_dprintf(2, "Error during environement variables initialisation\n");
		exit (1);
	}
	shell->tree = NULL;
	shell->p_ar.pipes = NULL;
	shell->p_ar.pipes_nb = 0;
	if (ft_fetch_env_vars(shell->env_vars, envp) == -1)
	{
		ft_dprintf(2, "Error during environement variables initialisation\n");
		ft_free_shell(shell);
		exit (1);
	}
	return (1);
}



int	main(int argc, char **argv, char **envp)
{
	t_token	*stack;
	t_shell	shell;


	int		token_error;
	int		syntax_error;
	int		tree_error;
	int		exit_status;

	exit_status = 0;
	if (argc != 2)
		return (1);
	token_error = 0;
	syntax_error = 0;
	tree_error = 0;
	stack = NULL;

	if (!ft_init_shell(&shell, envp))
		return(1);
	// printf("\n =============== PARSING ===============\n");
	token_error = tokenise(argv[1], &stack);
	if (token_error)
	{
		printf("tokenisation error: %s\n", ft_handle_token_errors(token_error));
		kill_stack(&stack);
		ft_free_shell(&shell);
		return (1);
	}
	syntax_error = check_syntax(stack);
	if (syntax_error)
	{
		kill_stack(&stack);
		ft_free_shell(&shell);
		return (2);
	}
	ft_redirections(&stack);
	shell.tree = ft_create_tree(&stack, &tree_error, 2);
	if (tree_error || !shell.tree)
	{
		ft_handle_tree_error(tree_error);
		// ft_free_tree(shell.tree);
		ft_free_shell(&shell);
		return (3);
	}
	ft_exec_root(shell.tree, &shell);
	// printf("exit status [%d]\n", ft_get_exit_status(&shell.shell_vars)); /// Debug
	exit_status = ft_get_exit_status(&shell.shell_vars);
	ft_free_shell(&shell);
	return (exit_status);
}
