/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_execute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:32:18 by nrea              #+#    #+#             */
/*   Updated: 2024/05/07 11:00:59 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_EXECUTE_H
# define PARSE_EXECUTE_H
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include "token.h"
# include "token_utils.h"
# include "libft.h"
# include "env_variables.h"

# define N_EXEC 0
# define N_PIPE 1
# define N_OR 2
# define N_AND 3

typedef enum e_side
{
	left,
	right,
	center
}			t_side;

typedef struct s_node
{
	int						type;
	union
	{
		struct
		{
			int				stdin;
			int				stdout;
			t_side			side;
			t_token			*redir;
			t_token			*cmd;
		};
		struct
		{
			struct s_node	*left;
			struct s_node	*right;
		};
	};
}			t_node;

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
	t_evar	*env_vars[58];
	t_svars	shell_vars;
	t_pipes	p_ar;
	t_node	*tree;
}	t_shell;

///PARSING
int			get_hd(t_token *tok, char *eof, t_shell *shell, t_token **stack);
int			ft_redirections(t_token **stack, t_shell *shell);
t_token		**ft_strip_bracket(t_token **stack);
int			ft_check_outer_brackets(t_token *stack);
int			split_token_lst(int rank, t_token **st, t_token **l, t_token **r);
int			ft_find_operator(int priority, t_token *stack);
t_node		*ft_create_tree(t_token **stack, int *error, int priority);
t_node		*ft_create_cond_node(t_token **stack, int op_rank, int *error);
t_node		*ft_create_pipe_node(t_token **stack, int op_rank, int *error);
t_node		*ft_create_exec_node(t_token **stack, int *error);
void		ft_free_tree(t_node **tree);
void		*ft_set_tree_error(int *error, int type, t_node *node);
char		*ft_handle_tree_error(int error);

///EXECUTION
void		exit_gracefully(t_shell *shell, int exit_status);
void		exit_sadly(t_shell *shell, int exit_status);

typedef int	(*t_builtin)(t_token *cmd, t_node *node ,t_shell *shell);

void		ft_free_shell(t_shell *shell);

int			ft_exec_root(t_node *tree_root, t_shell *shell);

void		ft_exec_binary(t_node *node, int pipe_nb, t_shell *shell);

int			ft_pipe_abort_safe(int pipe_lvl, t_shell *s);

int			ft_exec_pipe(t_node *node, int pipe_lvl, t_shell *s);
int			ft_count_pipes(t_node *node);

int			p_al(t_node *node, t_shell *shell);
int			init_p(int **p_ar, int pipes_nb);
void		ft_close_p_ar(int **p_ar, int pipes_nb);
int			ft_free_p_ar(int	**p_ar, int pipes_nb);

int			ft_apply_r_out(char *file);
int			ft_apply_r_append(char *file);
int			ft_apply_r_in(char *file);

int			ft_apply_r_heredoc(char *content);

void		ft_display_error_msg(char *cmd, char *error);

int			ft_get_full_cmd(char **full_cmd, char *content, t_shell *shell);
int			ft_token_to_array(t_token **cmd_list, char	***cmd_array);
int			ft_apply_redir(t_node *node);
int			ft_apply_pipe_redir(t_node *node, int p_lvl, t_shell *s);

t_builtin	ft_getbuiltin(char *cmd);
int			ft_is_builtin(t_node *node);
int			ft_exec_builtin(t_node *node, int pipe_lvl, t_shell *shell);
int			write_error(char *cmd, int exit_status);

char		*get_cwd(void);
int			pwd(t_token *cmd, t_node *node, t_shell *shell);
int			echo(t_token *cmd, t_node *node, t_shell *shell);
int			env(t_token *cmd, t_node *node, t_shell *shell);
int			export(t_token *cmd, t_node *node, t_shell *shell);
int			ft_display_vars(char *prefix, t_shell *shell);
int			unset(t_token *cmd, t_node *node, t_shell *shell);
int			cd(t_token *cmd, t_node *node, t_shell *shell);
int			bt_exit(t_token *cmd, t_node *node, t_shell *shell);
#endif
