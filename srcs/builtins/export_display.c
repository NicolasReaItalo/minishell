/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:18:00 by nrea              #+#    #+#             */
/*   Updated: 2024/05/06 14:19:56 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

static int	display_var(char *prefix, t_evar *var)
{
	if (write(1, prefix, ft_strlen(prefix)) < 0)
		return (0);
	if (write(1, " ", 1) < 0)
		return (0);
	if (write(1, var->key, ft_strlen(var->key)) < 0)
		return (0);
	if (var->value)
	{
		if (write(1, "=\"", 2) < 0)
			return (0);
		if (write(1, var->value, ft_strlen(var->value)) < 0)
			return (0);
		if (write(1, "\"", 1) < 0)
			return (0);
	}
	if (write(1, "\n", 1) < 0)
		return (0);
	return (1);
}

/*Displays the env var each var preceded by a prefix*/
int	ft_display_vars(char *prefix, t_shell *shell)
{
	t_evar	*var;
	int		i;

	var = NULL;
	i = 0;
	while (i < 58)
	{
		var = shell->env_vars[i];
		while (var)
		{
			if (!display_var(prefix, var))
				return (write_error("export", 1));
			var = var->next;
		}
		i++;
	}
	return (0);
}
