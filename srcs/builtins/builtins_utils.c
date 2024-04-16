/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:24:39 by nrea              #+#    #+#             */
/*   Updated: 2024/04/16 10:58:54 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

/*Returns 1 if the exec node calls for a built-in command, 0 otherwise*/
int	ft_is_builtin(t_node *node)
{
	char	*cmd;

	if (!node || node->type != N_EXEC || !node->cmd || !node->cmd->content)
		return (0);
	cmd = node->cmd->content;
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*return a function pointer to the builtin*/
t_builtin	ft_getbuiltin(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (!ft_strcmp(cmd, "echo"))
		return ((t_builtin) echo);
	else if (!ft_strcmp(cmd, "cd"))
		return ((t_builtin) cd);
	else if (!ft_strcmp(cmd, "export"))
		return ((t_builtin) export);
	else if (!ft_strcmp(cmd, "unset"))
		return ((t_builtin) unset);
	else if (!ft_strcmp(cmd, "pwd"))
		return ((t_builtin) pwd);
	else if (!ft_strcmp(cmd, "env"))
		return ((t_builtin) env);
	else if (!ft_strcmp(cmd, "exit"))
		return ((t_builtin) bt_exit);
	return (NULL);
}
