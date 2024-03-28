/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_fetch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:35:15 by nrea              #+#    #+#             */
/*   Updated: 2024/03/27 15:36:22 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"

/*returns the location of the first =*/
static int	ft_find_equal(char *du)
{
	int		i;

	i = 0;
	while (du[i] != '=')
	{
		if (!du[i])
		{
			free(du);
			return (-1);
		}
		i++;
	}
	return (i);
}

/*Separate the key and the value from the var in
the form key=value */
int	ft_separate_var(char *var, char **key, char **value)
{
	char	*du;
	int		i;

	du = ft_strdup(var);
	if (!du)
		return (-1);
	i = ft_find_equal(du);
	if (i == -1)
		return (-1);
	du[i] = '\0';
		*key = ft_strdup(du);
	if (!*key)
	{
		free(du);
		return (-1);
	}
	*value = ft_strdup(du + i + 1);
	if (*value == NULL)
	{
		free(du);
		free(*key);
		return (-1);
	}
	free(du);
	return (1);
}

/*Fetch the environment variables from **envp
and store these in the shell vars structure*/
int	ft_fetch_env_vars(t_evar *vars[58], char **envp)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (envp[i])
	{
		key = NULL;
		value = NULL;
		if (ft_separate_var(envp[i], &key, &value) == -1)
			return (-1);
		ft_set_var(key, value, vars, NULL);
		free(key);
		free(value);
		i++;
	}
	return (1);
}
