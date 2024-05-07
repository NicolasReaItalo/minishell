/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_evaluate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:13:15 by nrea              #+#    #+#             */
/*   Updated: 2024/05/07 13:26:58 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_tokenisation(char *line, t_token **stack, t_shell *shell)
{
	int	err_code;

	err_code = 0;
	err_code = tokenise(line, stack);
	if (err_code)
	{
		ft_dprintf(2, "tokenisation error: %s\n", ft_handle_tok_err(err_code));
		kill_stack(stack);
		*stack = NULL;
		free(line);
		ft_set_exit_status(2, &shell->shell_vars);
		if (err_code == 1)
			exit_sadly(shell, 1);
		return (-1);
	}
	free(line);
	return (0);
}

static int	apply_check_syntax(t_token **stack, t_shell *shell)
{
	int	error_code;

	error_code = check_syntax(*stack, shell);
	if (error_code)
	{
		kill_stack(stack);
		*stack = NULL;
		if (error_code == 130)
			ft_set_exit_status(130, &shell->shell_vars);
		else
			ft_set_exit_status(2, &shell->shell_vars);
		return (-1);
	}
	return (0);
}

static int	apply_redirections(t_token **stack, t_shell *shell)
{
	int	ret;

	ret = ft_redirections(stack);
	if (ret == 1)
	{
		write(2, "Internal error during redirection\n", 35);
		kill_stack(stack);
		*stack = NULL;
		ft_set_exit_status(2, &shell->shell_vars);
		exit_sadly(shell, 1);
	}
	return (0);
}

static int	apply_create_tree(t_token **stack, t_shell *shell)
{
	int		error_code;

	error_code = 0;
	shell->tree = ft_create_tree(stack, &error_code, 2);
	if (error_code)
	{
		ft_handle_tree_error(error_code);
		kill_stack(stack);
		ft_free_tree(&shell->tree);
		if (error_code == 5)
			exit_sadly(shell, 1);
		return (-1);
	}
	return (0);
}

/*Evaluate the line and create the parse_tree*/
int	evaluate(char *line, t_token **stack, t_shell *shell)
{
	if (apply_tokenisation(line, stack, shell) == -1)
		return (-1);
	if (apply_check_syntax(stack, shell) == -1)
		return (-1);
	if (apply_redirections(stack, shell) == -1)
		return (-1);
	if (apply_create_tree(stack, shell) == -1)
		return (-1);
	return (0);
}
