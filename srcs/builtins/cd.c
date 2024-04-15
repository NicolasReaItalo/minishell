/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:19:24 by nrea              #+#    #+#             */
/*   Updated: 2024/04/15 15:36:18 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

/*update PWD with newpwd and OLDPWD with the former value of PWD*/
static int	update_pwd(char *new_pwd, t_shell *s)
{
	char	*old_pwd;

	old_pwd = NULL;
	old_pwd = ft_get_var_value("PWD", s->env_vars, s->shell_vars);
	if (ft_set_var("OLDPWD", old_pwd, s->env_vars, &s->shell_vars) == -1)
	{
		write(2, "cd: Error during env var update\n", 33);
		return (1);
	}
	if (ft_set_var("PWD", new_pwd, s->env_vars, &s->shell_vars) == -1)
	{
		write(2, "cd: Error during env var update\n", 33);
		return (1);
	}
	return (0);
}

static int	cd_home(t_shell *shell)
{
	char	*home_path;

	home_path = NULL;
	home_path = ft_get_var_value("HOME", shell->env_vars, shell->shell_vars);
	if (ft_strlen(home_path) == 0)
	{
		write(2, "cd: HOME not set\n", 18);
		return (1);
	}
	if (chdir(home_path) == -1)
	{
		perror(home_path);
		return (1);
	}
	return (update_pwd(home_path, shell));
}

static int	get_cur_dir(char **buffer, int buffer_size)
{
	*buffer = malloc(buffer_size * sizeof(char));
	if (*buffer == NULL)
	{
		write(2, "pwd: Internal Error\n", 21);
		return (1);
	}
	ft_memset(*buffer, 0, buffer_size * sizeof(char));
	if (getcwd(*buffer, buffer_size) == NULL)
	{
		free(*buffer);
		if (errno == ERANGE && buffer_size <= 900)
			return (get_cur_dir(buffer, buffer_size * 2));
		else
		{
			perror("pwd");
			return (1);
		}
	}
	return (0);
}

int	cd(t_token *cmd, t_node *node, t_shell *shell)
{
	char	*cur_dir;

	(void) node;
	if (!cmd || !shell)
		return (1);
	cur_dir = NULL;
	cmd = cmd->next;
	if (!cmd)
		return (cd_home(shell));
	if (chdir(cmd->content) == -1)
	{
		perror(cmd->content);
		return (1);
	}
	if (get_cur_dir(&cur_dir, 100) == 1)
		return (1);
	if (update_pwd(cur_dir, shell) == 1)
	{
		free(cur_dir);
		return (1);
	}
	free(cur_dir);
	return (0);
}
