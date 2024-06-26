/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:14:48 by nrea              #+#    #+#             */
/*   Updated: 2024/05/07 11:55:28 by nrea             ###   ########.fr       */
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

static void	set_pwd(t_shell *shell)
{
	char	*cwd;

	cwd = NULL;
	cwd = get_cwd();
	if (!cwd)
	{
		ft_free_shell(shell);
		exit (1);
	}
	if (ft_set_var("PWD", cwd, shell->env_vars, &shell->shell_vars) == 0)
	{
		write(2, "Error during pwd initialisation\n", 33);
		ft_free_shell(shell);
		free(cwd);
		exit (1);
	}
	free(cwd);
}

static void	set_shlvl(t_shell *s, int level)
{
	char	*value;
	char	*n;

	if (level == -1)
	{
		value = ft_get_var_value("SHLVL", s->env_vars, s->shell_vars);
		level = ft_atoi(value);
		n = ft_itoa(level + 1);
		if (!n || !ft_set_var("SHLVL", n, s->env_vars, &s->shell_vars))
		{
			write(2, "Error during set SHLV\n", 23);
			ft_free_shell(s);
			if (n)
				free(n);
			exit(1);
		}
		free(n);
		return ;
	}
	if (!ft_set_var("SHLVL", "1", s->env_vars, &s->shell_vars))
	{
		write(2, "Error during set SHLV\n", 23);
		ft_free_shell(s);
		exit(1);
	}
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
	if (!isset("PWD", shell->env_vars))
		set_pwd(shell);
	if (!isset("SHLVL", shell->env_vars))
		set_shlvl(shell, 1);
	else
		set_shlvl(shell, -1);
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
