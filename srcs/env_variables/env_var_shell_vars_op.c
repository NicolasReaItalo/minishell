/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_shell_vars_op.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 10:27:51 by nrea              #+#    #+#             */
/*   Updated: 2024/03/19 11:42:35 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
#include "libft.h"

int	ft_isshell_var(char *key)
{
	if (!ft_strcmp(key, "?") || !ft_strcmp(key, "IFS"))
		return (1);
	return (0);
}

char	*ft_get_shell_var(char *key, t_svars shell_vars)
{
	if (!ft_strcmp(key, "?"))
		return (shell_vars.exit_code);
	if (!ft_strcmp(key, "IFS"))
		return (shell_vars.ifs);
	return ("");
}

/*
Modify the value of a shell variable
Return values : 1 :success
				0 : malloc error
				-1: incorrect identifier key*/
int	ft_set_shell_var(char *key, char *value, t_svars *svars)
{
	char	*val;

	val = NULL;
	if (!key || !svars)
		return (-1);
	if (!ft_strcmp(key, "IFS"))
	{
		if (value)
		{
			val = ft_strdup(value);
			if (!val)
				return (0);
		}
		free(svars->ifs);
		svars->ifs = val;
	}
	return (1);
}

/*
append the value to a shell variable
Return values : 1 :success
				0 : malloc error
				-1: incorrect identifier key*/
int	ft_append_s_var(char *key, char *value, t_evar **env_l, t_svars *svars)
{
	char	*or_val;
	char	*new_val;

	new_val = NULL;
	if (!key || !svars)
		return (-1);
	if (!ft_strcmp(key, "IFS"))
	{
		if (value)
		{
			or_val = ft_get_var_value(key, env_l, *svars);
			new_val = ft_strjoin(or_val, value);
			if (!new_val)
				return (0);
		}
		free(svars->ifs);
		svars->ifs = new_val;
	}
	return (1);
}
