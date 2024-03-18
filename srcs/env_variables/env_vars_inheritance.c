/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_inheritance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:41:59 by nrea              #+#    #+#             */
/*   Updated: 2024/03/18 17:42:39 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
#include "libft.h"
#include <stdio.h>

/*Fetch the environment variables from **envp
and store these in the shell vars structure*/
void	ft_fetch_env_vars(t_evar *vars[58], char **envp)
{
	char	**splitted;
	int		i;

	i = 0;
	while (envp[i])
	{
		splitted = ft_split(envp[i], '=');
		if (!splitted)
			return ;
		ft_set_var(splitted[0], splitted[1], vars);
		ft_free_splitted(splitted);
		splitted = NULL;
		i++;
	}
}

static int	ft_count_var(t_evar **vars)
{
	int		nb;
	int		i;
	t_evar	*var;

	nb = 0;
	i = 0;
	var = NULL;
	while (i < 58)
	{
		var = vars[i];
		while (var)
		{
			nb++;
			var = var->next;
		}
		i++;
	}
	return (nb);
}

/*concatenate the var in the form key=value*/
static char	*ft_concatenate(t_evar *var)
{
	char	*ret;
	char	*ret2;

	ret = NULL;
	ret2 = NULL;
	if (!var || !var->key)
		return (NULL);
	ret = ft_strjoin(var->key, "=");
	if (!ret)
		return (NULL);
	if (!var->value)
		return (ret);
	ret2 = ft_strjoin(ret, var->value);
	free(ret);
	if (!ret2)
		return (NULL);
	return (ret2);
}

static void	ft_populate(t_evar **vars, char	**envp)
{
	int		i;
	int		j;
	t_evar	*cur;

	i = 0;
	j = 0;
	while (i < 58)
	{
		cur = vars[i];
		while (cur)
		{
			envp[j] = ft_concatenate(cur);
			if (!envp[j])
			{
				ft_free_splitted(envp);
				return ;
			}
			j++;
			cur = cur->next;
		}
		i++;
	}
}

/*Allocate and copy the env variables in the form of a null terminated
 char** array suitable for the envp parameter of execve*/
char	**ft_push_env_vars(t_evar **vars)
{
	int		var_nb;
	char	**envp;

	var_nb = ft_count_var(vars);
	envp = malloc((var_nb + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	ft_memset(envp, 0, (var_nb + 1) * sizeof(char *));
	ft_populate(vars, envp);
	return (envp);
}
