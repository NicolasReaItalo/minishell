/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:32:18 by nrea              #+#    #+#             */
/*   Updated: 2024/03/26 14:02:11 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include "parser.h"
# include "token.h"
# include "token_utils.h"
# include "libft.h"
# include "env_variables.h"

typedef struct s_pipes
{
	int		**pipes;
	int		pipes_nb;
}	t_pipes;

typedef struct s_exec
{
	char	**cmd_array;
	char	**env_array;
}	t_exec;

typedef struct s_shell
{
	t_evar	*env_vars[58]; // variables d'environnement
	t_svars	shell_vars;// variables de shell speciales
	t_pipes	pipe_ar; // pipes
	t_node	*tree; // pointeur vers le parse_tree pour le free
					//dans un subprocess en cas de builtin ou
					//d'echec de excve
}	t_shell;

void		ft_free_shell(t_shell *shell);

void		ft_exec_root(t_node *tree_root, t_shell *shell);

void		ft_exec(t_node *node, int pipe_nb, t_shell *shell);

void		ft_exec_pipe(t_node *node, int pipe_nb, t_shell *shell);

int			ft_count_pipes(t_node *node);
int			ft_create_pipe_ar(t_node *node, t_shell *shell);
int			ft_init_pipe_ar(int **pipe_ar, int pipes_nb);
void		ft_close_pipe_ar(int **pipe_ar, int pipes_nb);
int			ft_free_pipe_ar(int	**pipe_ar, int pipes_nb);

int			ft_apply_r_out(char *file);
int			ft_apply_r_append(char *file);
int			ft_apply_r_in(char *file);

int			ft_apply_r_heredoc(char *content);

void		ft_display_error_msg(char *cmd, char *error);
int			ft_get_full_cmd(char **full_cmd, char *content, t_shell *shell);
int			ft_token_to_array(t_token **cmd_list, char	***cmd_array);

int			ft_apply_redir(t_node *node);
int			ft_apply_pipe_redir(t_node *node, int p_lvl, t_shell *s);


#endif
