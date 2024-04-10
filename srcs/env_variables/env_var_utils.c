/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:35:44 by nrea              #+#    #+#             */
/*   Updated: 2024/04/10 13:18:58 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
/*initialisation a 0 de la structure des varables d'environnement
probablement a regrouper avec une fonction d'initialisation
de toutes les variables de la structure shell */
int	ft_init_env_vars(t_evar	*vars[58], t_svars *shell_vars)
{
	ft_memset(vars, 0, 58 * sizeof(t_evar *));
	shell_vars->exit_code = ft_strdup("0");
	if (!shell_vars->exit_code)
		return (0);
	shell_vars->ifs = ft_strdup(" \t\n");
	if (!shell_vars->ifs)
	{
		free(shell_vars->exit_code);
		return (0);
	}
	return (1);
}

void	*ft_free_var(t_evar *var)
{
	if (!var)
		return (NULL);
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(var);
	return (NULL);
}

void	ft_free_env_vars(t_evar *env_list[58], t_svars *shell_vars)
{
	int		i;
	t_evar	*prev;
	t_evar	*cur;

	i = 0;
	while (i < 58)
	{
		prev = NULL;
		cur = NULL;
		if (env_list[i])
		{
			cur = env_list[i];
			while (cur)
			{
				prev = cur;
				cur = cur->next;
				ft_free_var(prev);
			}
		}
		i++;
	}
	free(shell_vars->exit_code);
	free(shell_vars->ifs);
}

int	ft_free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (0);
}

/*Checks if the key  string is a valid key for an environement
variable
return 1 in cqse o success, 0 otherwise
RULES
no empty string
char : a-z or A-Z or 1-9 or _
first char must not be a  digit*/
int	ft_is_valid_key(char *key)
{
	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (*key)
	{
		if (!ft_isalpha(*key) && !ft_isdigit(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}
