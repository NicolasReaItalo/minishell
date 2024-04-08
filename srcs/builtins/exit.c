/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/04/08 15:20:13 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_valid_status(char *content)
{
	int	i;

	while (*content && *content == ' ')
		content++;
	i = 0;
	while (content[i])
	{
		if (content[i] == ' ')
			break ;
		if (i >= 19)
			return (0);
		if (!ft_isdigit(content[i]) && content[i] != '-' && content[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

static int	wrong_status(char *content)
{
	char	*part1;
	char	*msg;

	part1 = ft_strjoin("exit :", content);
	if (!part1)
	{
		write(2, "Internal error\n", 16);
		return (1);
	}
	msg = ft_strjoin(part1, ": numeric argument required\n");
	if (!msg)
	{
		free(part1);
		write(2, "Internal error\n", 16);
		return (1);
	}
	write(2, msg, ft_strlen(msg));
	free(part1);
	free(msg);
	return (2);
}

int	bt_exit(t_token *cmd, t_shell *shell)
{
	int	status;

	write(1, "Exiting Minishell. See you soon!\n", 34);
	if (!cmd)
		return (1);
	cmd = cmd->next;
	if (!cmd)
	{
		ft_free_shell(shell);
		exit (0);
	}
	if (!is_valid_status(cmd->content))
	{
		wrong_status(cmd->content);
		ft_free_shell(shell);
		exit (2);
	}
	status = ft_atoi(cmd->content);
	ft_free_shell(shell);
	exit (status);
}
