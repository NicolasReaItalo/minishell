/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:46:46 by nrea              #+#    #+#             */
/*   Updated: 2024/03/18 17:59:51 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
#include "libft.h"
#include <stdio.h>

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
char	*ft_get_var_value(char *key, t_evar *env_list[58])
{
	int		index;
	t_evar	*var;

	if (!ft_is_valid_key(key) || !env_list)
		return ("");
	index = key[0] - 65;
	if (index < 0)
		return ("");
	var = env_list[index];
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
