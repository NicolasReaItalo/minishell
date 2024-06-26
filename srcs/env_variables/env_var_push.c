/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:41:59 by nrea              #+#    #+#             */
/*   Updated: 2024/04/16 17:57:01 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"

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
			if (var->value)
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

static int	ft_populate(t_evar **vars, char	***envp)
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
			if (cur->value)
			{
				(*envp)[j] = ft_concatenate(cur);
				if ((*envp)[j] == NULL)
					return (0);
				j++;
			}
			cur = cur->next;
		}
		i++;
	}
	return (1);
}

/*Allocate and copy the env variables in the form of a null terminated
 char** array suitable for the envp parameter of execve*/
int	ft_push_env_vars(t_evar **vars, char ***envp)
{
	int		var_nb;

	var_nb = ft_count_var(vars);
	*envp = (char **) malloc((var_nb + 1) * sizeof(char *));
	if (!*envp || !envp)
		return (0);
	ft_memset(*envp, 0, (var_nb + 1) * sizeof(char *));
	if (!ft_populate(vars, envp))
	{
		ft_free_splitted(*envp);
		return (0);
	}
	return (1);
}
