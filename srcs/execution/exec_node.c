/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:50:23 by nrea              #+#    #+#             */
/*   Updated: 2024/03/25 19:18:47 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*convert the cmd list to an array** of char* with every token content
 initialise the cmd_array passed in parameter
return 1 in case of success, 0 otherwise
*/
int	ft_token_to_array(t_token **cmd_list, char	***cmd_array)
{
	int		size;
	int		i;
	t_token	*node;

	size = ft_stack_size(*cmd_list);
	*cmd_array = (char **) malloc((size + 1) * sizeof(char *));
	if (!*cmd_array)
		return (0);
	node = *cmd_list;
	i = 0;
	while (node)
	{
		(*cmd_array)[i] = ft_strdup(node->content);
		if (!(*cmd_array)[i])
		{
			ft_free_splitted(*cmd_array);
			return (0);
		}
		i++;
		node = node->next;
	}
	(*cmd_array)[i] = NULL;
	kill_stack(cmd_list);
	return (1);
}

char	*ft_join_paths(char const *path, char const *cmd)
{
	char	*full_path;
	int		i;
	int		j;

	if (!path || !cmd)
		return (NULL);
	full_path = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!full_path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		full_path[i] = path[i];
		i++;
	}
	full_path[i] = '/';
	i++;
	j = 0;
	while (cmd[j])
	{
		full_path[i + j] = cmd[j];
		j++;
	}
	full_path[i + j] = '\0';
	return (full_path);
}

/*Create the full path command by browsing the PATH variable
Return 0 in case of success
1 in case of malloc error
127 : the path does not exist
*/
int	ft_get_full_cmd(char **full_cmd, char *content, t_shell *shell)
{
	char	**paths;
	int		i;
	char	*var_path;

	var_path = ft_get_var_value("PATH", shell->env_vars, shell->shell_vars);
	paths = ft_split(var_path, ':');
	i = 0;
	while (paths[i])
	{
		*full_cmd = NULL;
		*full_cmd = ft_join_paths(paths[i], content);
		if (!full_cmd)
			return (1);
		if (access(*full_cmd, F_OK) == 0)
			return (0);
		free(*full_cmd);
		i++;
	}
	ft_free_splitted(paths);
	return (127);
}

/*Apply the redirections of the pipes*/
int	ft_apply_pipe_redir(t_node *node, int pipe_nb, t_shell *shell)
{

	if (node->side == left)
		{
			if (dup2(shell->pipe_array.pipes[pipe_nb][1], STDOUT_FILENO) == -1 )
			{
				ft_close_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
				ft_free_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
				write(2, "Error during dup2 !!!\n", 23);
				return (-1);
			}
		}
		else if (node->side == right)
		{
			if (dup2(shell->pipe_array.pipes[pipe_nb][0], STDIN_FILENO) == -1 )
			{
				ft_close_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
				ft_free_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
				write(2, "Error during dup2 !!!\n", 23);
				return (-1);
			}
			if (pipe_nb > 0)
			{
				if (dup2(shell->pipe_array.pipes[pipe_nb - 1][1], STDOUT_FILENO) == -1 )
				{
					ft_close_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
					ft_free_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
					write(2, "Error during dup2 !!!\n", 23);
					return (-1);
				}
			}
		}
		ft_close_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
		ft_free_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
	return (0);
}

/*Exit safely the ft_exec function
Displays eror msg in case of internal error or cmd not found*/
int	ft_exec_exit_safe(int exit_status, t_shell *shell, t_exec exec, char *fullcmd)
{
	if (exit_status == 1)
		write(2, "Internal Error\n", 16);
	else if (exit_status == 127)
	{
		if (fullcmd)
			write(2, fullcmd, ft_strlen(fullcmd));
		write(2, ": command not found\n", 21);
	}
	if (shell)
		ft_free_shell(shell);
	if (exec.cmd_array)
		ft_free_splitted(exec.cmd_array);
	if (exec.env_array)
		ft_free_splitted(exec.env_array);
	if (fullcmd)
		free(fullcmd);
	exit (exit_status);
}

		//[3]  gerer les redirections heredocs etc... => on retourne -1 en cas d'erreur
int	ft_apply_redir(t_node *node)
{
	t_token	*redir;
	int		ret;

	ret = 0;
	redir = node->redir;
	while(redir)
	{
		if (redir->type == R_OUT)
			ret = ft_apply_r_out(redir->content);
		else if (redir->type == R_IN)
			ret = ft_apply_r_in(redir->content);
		else if (redir->type == R_APPEND)
			ret = ft_apply_r_append(redir->content);
		else if (redir->type == R_HEREDOC)
			ret = ft_apply_r_heredoc(redir->content);
		if (ret)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

/*looks for a command in the frst token of the cmd list n node exec*/
void	ft_look_for_cmd(t_node *node, t_shell *shell, char **full_cmd, t_exec exec)
{
	struct stat	file_stat;
	int			ret;

	*full_cmd = NULL;
	if (ft_strchr(node->cmd->content, '/') != NULL)  // detection de '/'
	{
		*full_cmd = ft_strdup(node->cmd->content);
		if (!*full_cmd)
			ft_exec_exit_safe(1, shell, exec, *full_cmd);
		if (access(*full_cmd, F_OK) != 0 )
			ft_exec_exit_safe(127, shell, exec, *full_cmd);
	}
	else
	{
		ret = ft_get_full_cmd(full_cmd ,node->cmd->content, shell);
		if (ret != 0)
			ft_exec_exit_safe(ret, shell, exec, *full_cmd);
	}
	if (stat(*full_cmd, &file_stat) == -1)
		ft_exec_exit_safe(1, shell, exec, *full_cmd);
	if (!S_ISREG(file_stat.st_mode) || !(file_stat.st_mode & S_IXUSR)) /// A corriger
	{
		write(2, *full_cmd, ft_strlen(*full_cmd));
		if (S_ISDIR(file_stat.st_mode))
			write(2, ": Is a directory\n", 18);
		else
			write(2, ": Permission denied\n", 21);
		ft_exec_exit_safe(126, shell, exec, *full_cmd);
	}
}


/*cmd called to execute a node_exec  */
void	ft_exec(t_node *node, int pipe_nb, t_shell *shell)
{
	t_exec		exec;
	char		*full_cmd;

	exec.cmd_array = NULL;
	exec.env_array = NULL;
	full_cmd = NULL;
	if (pipe_nb != -1)
	{
		if(ft_apply_pipe_redir(node, pipe_nb,shell) == -1)
			ft_exec_exit_safe(1, shell, exec, full_cmd);
	}
	if (ft_apply_redir(node) == -1)
		ft_exec_exit_safe(1, shell, exec, full_cmd);
	if (node->cmd == NULL) /////[4] Si pas de token commande => free et  exit(0)
		ft_exec_exit_safe(0, shell, exec, full_cmd);
	ft_look_for_cmd(node, shell, &full_cmd, exec);
	if (!ft_token_to_array(&node->cmd, &exec.cmd_array))
		ft_exec_exit_safe(1, shell, exec, full_cmd);
	if (!ft_push_env_vars(shell->env_vars, &exec.env_array))
		ft_exec_exit_safe(1, shell, exec, full_cmd);
	if (execve(full_cmd, exec.cmd_array , exec.env_array) == -1) /////////[7] lancer execve => si echec ( free et exit code = 1 )
		ft_exec_exit_safe(1, shell, exec, full_cmd);
}
