/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:55:49 by nrea              #+#    #+#             */
/*   Updated: 2024/04/16 13:24:20 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

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

static char	*ft_join_paths(char const *path, char const *cmd)
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
int	ft_get_full_cmd(char **full_cmd, char *cont, t_shell *shell)
{
	char	**paths;
	int		i;
	char	*var_path;

	if (!ft_strlen(cont) || !ft_strcmp(".", cont) || !ft_strcmp("..", cont))
		return (127);
	var_path = ft_get_var_value("PATH", shell->env_vars, shell->shell_vars);
	paths = ft_split(var_path, ':');
	if (!paths)
		return (1);
	i = 0;
	while (paths[i])
	{
		*full_cmd = NULL;
		*full_cmd = ft_join_paths(paths[i], cont);
		if (!full_cmd)
			return (1);
		if (access(*full_cmd, F_OK) == 0)
			return (ft_free_splitted(paths));
		free(*full_cmd);
		i++;
	}
	ft_free_splitted(paths);
	*full_cmd = NULL;
	return (127);
}

void	ft_display_error_msg(char *cmd, char *error)
{
	char	*msg;

	if (!error)
		return ;
	msg = NULL;
	if (cmd)
		msg = ft_strjoin(cmd, error);
	if (msg)
		write(2, msg, ft_strlen(msg));
	else
		write(2, "Internal Error\n", 16);
	free(msg);
}

/*
An error has occured: malloc, pipe, fork...
we wait for all the child processes
then close all the pipes and free the pipe array.
*/
int	ft_pipe_abort_safe(int pipe_lvl, t_shell *s)
{
	write(2, "Internal Error\n", 16);
	if (pipe_lvl == 0)
	{
		if (s->p_ar.pipes_nb != 0 && s->p_ar.pipes != NULL)
		{
			ft_close_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
			ft_free_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
			s->p_ar.pipes_nb = 0;
		}
		s->p_ar.pipes_nb = 0;
		while (wait(NULL) != -1)
		{
		}
		ft_set_exit_status(1, &s->shell_vars);
	}
	return (-1);
}
