/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:14:48 by nrea              #+#    #+#             */
/*   Updated: 2024/04/08 14:39:52 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_shell(t_shell *shell)
{
	ft_free_env_vars(shell->env_vars, &shell->shell_vars);
	if (shell->tree)
		ft_free_tree(&shell->tree);
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
