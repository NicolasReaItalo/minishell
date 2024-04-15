/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/04/15 15:39:13 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

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

int	bt_exit(t_token *cmd, t_node *node, t_shell *shell)
{
	int	status;

	write(1, "\033[3;243mExiting Minishell... See you soon!\n\033[0m", 48);
	if (!cmd)
		return (1);
	cmd = cmd->next;
	close(node->stdin);
	close(node->stdout);
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
