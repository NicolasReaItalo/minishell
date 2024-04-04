/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/04/04 13:44:19 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
/*
 Each variable or function specified by name shall be unset.
Unsetting a variable or function that was not previously set shall
not be considered an error and does not  cause  the  shell  to abort.
 Note that:
VARIABLE=
is  not  equivalent to an unset of VARIABLE; in the example,
VARIABLE is set to "".
*/
int	unset(t_token *cmd, t_shell *shell)
{
	cmd = cmd->next;
	while (cmd)
	{
		ft_unset_var(cmd->content, shell->env_vars);
		cmd = cmd->next;
	}
	return (0);
}
