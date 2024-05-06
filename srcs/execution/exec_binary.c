/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:50:23 by nrea              #+#    #+#             */
/*   Updated: 2024/05/06 10:44:30 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

/*Exit safely the ft_exec function
Displays eror msg in case of internal error*/
static int	ft_exec_exit_err(int status, t_shell *s, t_exec exec, char *cmd)
{
	if (status == 1)
		ft_display_error_msg(NULL, "Internal Error");
	if (s)
		ft_free_shell(s);
	if (exec.cmd_array)
		ft_free_splitted(exec.cmd_array);
	if (exec.env_array)
		ft_free_splitted(exec.env_array);
	if (cmd)
		free(cmd);
	exit (status);
}

/*Similar to ft_exit_err but wo't display an error msg in case
of exit_status == 1
Useful in case of redir error bc the error displaye is handled
by perror()*/
static int	ft_exec_exit_simple(int status, t_shell *s, t_exec exec, char *cmd)
{
	if (s)
		ft_free_shell(s);
	if (exec.cmd_array)
		ft_free_splitted(exec.cmd_array);
	if (exec.env_array)
		ft_free_splitted(exec.env_array);
	if (cmd)
		free(cmd);
	exit (status);
}

/* Checks if the cmd file is a regular file and is executable */
/// A corriger pour la partie exceutable
int	ft_check_status(char *file)
{
	struct stat	file_stat;

	if (stat(file, &file_stat) == -1)
		return (1);
	if (!S_ISREG(file_stat.st_mode) || !(file_stat.st_mode & S_IXUSR))
	{
		if (S_ISDIR(file_stat.st_mode))
			ft_display_error_msg(file, ": Is a directory\n");
		else
			ft_display_error_msg(file, ": Permission denied\n");
		return (126);
	}
	return (0);
}

/*looks for a command in the first token of the cmd list in node exec
Assign the result to the pointer fullcmd
if the content of the token contains '/' the command is
considered absolute or relative path and no path lookup is done
else we try to build a valid path using the PATH variable*/
void	ft_look_for_cmd(t_node *node, t_shell *s, char **full_cmd, t_exec exec)
{
	int			ret;

	if (ft_strchr(node->cmd->content, '/') != NULL)
	{
		*full_cmd = ft_strdup(node->cmd->content);
		if (!*full_cmd)
			ft_exec_exit_err(1, s, exec, *full_cmd);
		if (access(*full_cmd, F_OK) != 0)
		{
			ft_display_error_msg(*full_cmd, ": No such file or directory\n");
			ft_exec_exit_err(127, s, exec, *full_cmd);
		}
	}
	else
	{
		ret = ft_get_full_cmd(full_cmd, node->cmd->content, s);
		if (ret != 0)
		{
			ft_display_error_msg(node->cmd->content, ": Command not found\n");
			ft_exec_exit_err(ret, s, exec, *full_cmd);
		}
	}
	ret = ft_check_status(*full_cmd);
	if (ret != 0)
		ft_exec_exit_err(ret, s, exec, *full_cmd);
}

/*cmd called to execute a node_exec  */
void	ft_exec_binary(t_node *node, int pipe_lvl, t_shell *shell)
{
	t_exec		exec;
	char		*full_cmd;

	exec.cmd_array = NULL;
	exec.env_array = NULL;
	full_cmd = NULL;
	if (pipe_lvl != -1)
	{
		if (!shell->p_ar.pipes || shell->p_ar.pipes == NULL)
			ft_exec_exit_err(1, shell, exec, full_cmd);
		if (ft_apply_pipe_redir(node, pipe_lvl, shell) == -1)
			ft_exec_exit_err(1, shell, exec, full_cmd);
	}
	if (ft_apply_redir(node) == -1)
		ft_exec_exit_simple(1, shell, exec, full_cmd);
	if (node->cmd == NULL)
		ft_exec_exit_err(0, shell, exec, full_cmd);
	ft_look_for_cmd(node, shell, &full_cmd, exec);
	if (!ft_token_to_array(&node->cmd, &exec.cmd_array))
		ft_exec_exit_err(1, shell, exec, full_cmd);
	if (!ft_push_env_vars(shell->env_vars, &exec.env_array))
		ft_exec_exit_err(1, shell, exec, full_cmd);
	if (execve(full_cmd, exec.cmd_array, exec.env_array) == -1)
		ft_exec_exit_err(1, shell, exec, full_cmd);
}
