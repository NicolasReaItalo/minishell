/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/05/06 14:36:00 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

static int	display_var(char *var)
{
	if (write(1, var, ft_strlen(var)) < 0)
		return (0);
	if (write(1, "\n", 1) < 0)
		return (0);
	return (1);
}

int	env(t_token *cmd, t_node *node, t_shell *shell)
{
	char	**vars;
	int		i;

	(void) node;
	if (cmd->next)
	{
		write(2, "env: No option or argument must be provided\n", 45);
		return (125);
	}
	vars = NULL;
	if (ft_push_env_vars(shell->env_vars, &vars) == 0)
	{
		write(2, "An error has occured during the variables retrieval\n", 53);
		return (125);
	}
	i = 0;
	while (vars[i])
	{
		if (!display_var(vars[i]))
			return (write_error("env", 125));
		i++;
	}
	ft_free_splitted(vars);
	return (0);
}
