/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/05/01 12:27:00 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

static int	exit_echo(int trailing_nl)
{
	if (trailing_nl)
		write(1, "\n", 1);
	return (0);
}

static int	arg_valid(char *arg)
{
	arg++;
	while (*arg)
	{
		if (*arg != 'n')
			return (0);
		arg++;
	}
	return (1);
}

static int	display(t_token *cmd)
{
	int	trailing_nl;
	int	accept_args;

	trailing_nl = 1;
	accept_args = 1;
	while (cmd)
	{
		if (cmd->content[0] == '-' && accept_args && arg_valid(cmd->content))
		{
			trailing_nl = 0;
			cmd = cmd->next;
			continue ;
		}
		else
			accept_args = 0;
		write(1, cmd->content, ft_strlen(cmd->content));
		if (cmd->next)
			write(1, " ", 1);
		cmd = cmd->next;
	}
	return (trailing_nl);
}

int	echo(t_token *cmd, t_node *node, t_shell *shell)
{
	(void) node;
	(void) shell;
	if (!cmd)
		return (1);
	cmd = cmd->next;
	if (!cmd)
		return (exit_echo(1));
	return (exit_echo(display(cmd)));
}
