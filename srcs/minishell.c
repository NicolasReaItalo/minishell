/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/05 11:03:49 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"


char	*ft_handle_tok_err(int error)
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
	rl_clear_history();

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
	char	*line;

	token_error = 0;
	syntax_error = 0;
	tree_error = 0;
	stack = NULL;

	(void) argc;
	(void) argv;

	if (!ft_init_shell(&shell, envp))
		return(1);
	while(1)
	{
	line = readline( "minishell> " );
	if (line && ft_strlen(line))
	{
		add_history(line);
		token_error = tokenise(line, &stack);
		if (token_error)
		{
			ft_dprintf(2, "tokenisation error: %s\n", ft_handle_tok_err(token_error));
			kill_stack(&stack);
			free(line);
			continue ;
		}
		free(line);
		syntax_error = check_syntax(stack);
		if (syntax_error)
		{
			kill_stack(&stack);
			continue ;
		}
		ft_redirections(&stack); // ajouter gestion erreur
		shell.tree = ft_create_tree(&stack, &tree_error, 2);
		if (tree_error || !shell.tree)
		{
			ft_handle_tree_error(tree_error);
			continue ;
		}
		ft_exec_root(shell.tree, &shell);
		ft_free_tree(shell.tree);
		stack = NULL;
	}
	}
	ft_free_shell(&shell);
	return (0);
	}
