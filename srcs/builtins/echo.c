/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/04/03 17:06:40 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	exit_echo(int trailing_nl)
{
	if (trailing_nl)
		write(1, "\n", 1);
	return (0);
}

int	echo(t_token *cmd, t_shell *shell)
{
	int	trailing_nl;

	(void) shell;
	if (!cmd)
		return (1);
	trailing_nl = 1;
	cmd = cmd->next;
	if (!cmd)
		return (exit_echo(trailing_nl));
	if (!strcmp(cmd->content, "-n"))
	{
		trailing_nl = 0;
		cmd = cmd->next;
	}
	while (cmd)
	{
		write(1, cmd->content, ft_strlen(cmd->content));
		if (cmd->next)
			write(1, " ", 1);
		cmd = cmd->next;
	}
	return (exit_echo(trailing_nl));
}
