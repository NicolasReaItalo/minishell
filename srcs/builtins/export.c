/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:26:04 by nrea              #+#    #+#             */
/*   Updated: 2024/04/16 18:17:02 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

static int	msg_invalid_id(char *content)
{
	char	*msg;
	char	*msgf;

	msg = NULL;
	msgf = NULL;
	msg = ft_strjoin(content, "' : not a valid identifier\n");
	if (!msg)
	{
		write(2, "export : Internal Error\n", 25);
		free(content);
		return (1);
	}
	msgf = ft_strjoin("export : '", msg);
	if (!msgf)
		write(2, "export : Internal Error\n", 25);
	else
		write(2, msgf, ft_strlen(msgf));
	free(msg);
	free(msgf);
	free(content);
	return (1);
}

/*Displays the env var each var preceded by a prefix*/
int	ft_display_vars(char *prefix, t_shell *shell)
{
	char	**vars;
	int		i;

	vars = NULL;
	if (ft_push_env_vars(shell->env_vars, &vars) == 0)
	{
		write(2, "An error has occured during the variables retrieval\n", 53);
		return (1);
	}
	i = 0;
	while (vars[i])
	{
		if (prefix)
			write(1, prefix, ft_strlen(prefix));
		write(1, vars[i], ft_strlen(vars[i]));
		write(1, "\n", 1);
		i++;
	}
	ft_free_splitted(vars);
	return (0);
}

/*return  1 in case of succes, -1 otherwise*/
static int	set_append(char *content, char *sep, t_shell *shell)
{
	char	*key;
	char	*or_content;
	char	*val;

	or_content = ft_strdup(content);
	if (!or_content)
	{
		write(2, "export : Internal Error\n", 25);
		return (-1);
	}
	sep[0] = '\0';
	val = sep + 2;
	key = content;
	if (!ft_is_valid_key(key) || ft_isshell_var(key))
		return (msg_invalid_id(or_content));
	free(or_content);
	if (ft_append_var(key, val, shell->env_vars, &shell->shell_vars) != 1)
	{
		write(2, "export : Internal Error\n", 25);
		return (-1);
	}
	return (1);
}

static int	set(char *content, char *sep, t_shell *shell)
{
	char	*key;
	char	*or_content;
	char	*val;

	key = NULL;
	val = NULL;
	or_content = ft_strdup(content);
	if (!or_content)
		return (write(2, "export : Internal Error\n", 25), -1);
	key = content;
	if (sep)
	{
		sep[0] = '\0';
		val = sep + 1;
	}
	else
		val = NULL;
	if (!ft_is_valid_key(key) || ft_isshell_var(key))
		return (msg_invalid_id(or_content));
	free(or_content);
	if (ft_set_var(key, val, shell->env_vars, &shell->shell_vars) != 1)
		return (write(2, "export : Internal Error\n", 25), -1);
	return (0);
}

int	export(t_token *cmd, t_node *node, t_shell *shell)
{
	char	*sep;

	(void) node;
	sep = NULL;
	cmd = cmd->next;
	if (cmd == NULL)
		return (ft_display_vars("declare -x ", shell));
	while (cmd)
	{
		sep = ft_strnstr(cmd->content, "+=", ft_strlen(cmd->content));
		if (sep)
		{
			if (set_append(cmd->content, sep, shell) == -1)
				return (1);
		}
		else
		{
			sep = ft_strnstr(cmd->content, "=", ft_strlen(cmd->content));
			if (set(cmd->content, sep, shell) == -1)
				return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}
