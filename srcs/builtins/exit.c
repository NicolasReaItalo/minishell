/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/04/16 15:45:42 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

static int	is_valid_status(char *content)
{
	int		i;
	char	neg;

	neg = '+';
	while (*content && *content == ' ')
		content++;
	if (*content && (*content == '+' || *content == '-'))
	{
		neg = *content;
		content++;
	}
	i = 0;
	while (content[i] && (i <= 19) && ft_isdigit(content[i]))
		i++;
	if (content[i] != '\0')
		return (0);
	if (neg == '-')
	{
		if (ft_strcmp(content, "9223372036854775809") >= 0)
			return (0);
	}
	else
		if (ft_strcmp(content, "9223372036854775808") >= 0)
			return (0);
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
	msg = ft_strjoin(part1, " : numeric argument required\n");
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

static int	exit_count_args(t_token *cmd)
{
	int	count;

	count = 0;
	if (!cmd)
		return (-1);
	else
		cmd = cmd->next;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	if (count > 1)
	{
		write(2, "exit: too many arguments\n", 26);
		return (-1);
	}
	return (1);
}

int	bt_exit(t_token *cmd, t_node *node, t_shell *shell)
{
	int	status;

	if (node->side == center)
		write(1, "exit\n", 6);
	if (exit_count_args(cmd) == -1)
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
