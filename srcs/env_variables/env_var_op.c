/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:46:46 by nrea              #+#    #+#             */
/*   Updated: 2024/03/19 13:56:33 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
/*unset an env variable identifie by the key parameter*/
void	ft_unset_var(char *key, t_evar **vars)
{
	int		index;
	t_evar	*cur;
	t_evar	*prev;
	t_evar	*next;

	index = key[0] - 65;
	if (!ft_is_valid_key(key) || index < 0 || index > 57 || !vars[index])
		return ;
	cur = vars[index];
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			next = cur->next;
			ft_free_var(cur);
			if (prev)
				(prev)->next = next;
			else
				vars[index] = next;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

/*get the value of the var identified by key
ifthe var doesn't exists or it's value is null -> returns ""*/
char	*ft_get_var_value(char *key, t_evar	*env_vars[58], t_svars shell_vars)
{
	int		index;
	t_evar	*var;

	if (ft_isshell_var(key))
		return (ft_get_shell_var(key, shell_vars));
	if (!ft_is_valid_key(key) || !env_vars)
		return ("");
	index = key[0] - 65;
	if (index < 0)
		return ("");
	var = env_vars[index];
	while (var)
	{
		if (!ft_strcmp(key, var->key))
		{
			if (var->value)
				return (var->value);
			else
				return ("");
		}
		var = var->next;
	}
	return ("");
}

/*Similar to ft_set_var but append the value at the end of the var value
like the export builtin with +=
Return values : 1 :success
				0 : malloc error
				-1: incorrect identifier key */
int	ft_append_var(char *key, char *value, t_evar **env_l, t_svars *svars)
{
	t_evar	*var;
	int		index;
	char	*or_val;
	char	*new_val;

	new_val = NULL;
	if (ft_isshell_var(key))
		return (ft_append_s_var(key, value, env_l, svars));
	if (!ft_is_valid_key(key) || ft_get_index(key[0], &index) == -1)
		return (-1);
	var = ft_get_var(key, env_l[index]);
	if (!var)
		return (ft_create_and_place(key, value, &env_l[index]));
	else
	{
		or_val = ft_get_var_value(key, env_l, *svars);
		new_val = ft_strjoin(or_val, value);
		if (!new_val)
			return (0);
		if (var->value)
			free((var)->value);
		(var)->value = new_val;
	}
	return (1);
}
