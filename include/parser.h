/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:43:49 by nrea              #+#    #+#             */
/*   Updated: 2024/03/11 14:58:01 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
# include "token_utils.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>

# define N_EXEC 0
# define N_PIPE 1
# define N_OR 2
# define N_AND 3

typedef struct s_node
{
	int						type;
	union
	{
		struct
		{
			int				in;
			int				out;
			int				bultin;
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

int		ft_capture_here_doc(t_token *tok, char *eof);
int		ft_redirections(t_token **stack);
t_token	**ft_strip_bracket(t_token **stack);
int		ft_check_outer_brackets(t_token *stack);
int		ft_split_token_list(int rank, t_token **st, t_token **l, t_token **r);
int		ft_find_operator(int priority, t_token *stack);

t_node	*ft_create_tree(t_token **stack, int *error, int priority);
t_node	*ft_create_cond_node(t_token **stack, int op_rank, int *error);
t_node	*ft_create_pipe_node(t_token **stack, int op_rank, int *error);
t_node	*ft_create_exec_node(t_token **stack);
void	ft_free_tree(t_node *tree);
void	*ft_set_tree_error(int *error, int type, t_node *node);
char	*ft_handle_tree_error(int error);
#endif
