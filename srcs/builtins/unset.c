/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/04/15 15:57:25 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"
/*
 Each variable or function specified by name shall be unset.
Unsetting a variable or function that was not previously set shall
not be considered an error and does not  cause  the  shell  to abort.
 Note that:
VARIABLE=
is  not  equivalent to an unset of VARIABLE; in the example,
VARIABLE is set to "".
*/
int	unset(t_token *cmd, t_node *node, t_shell *shell)
{
	(void) node;
	cmd = cmd->next;
	while (cmd)
	{
		ft_unset_var(cmd->content, shell->env_vars);
		cmd = cmd->next;
	}
	return (0);
}
