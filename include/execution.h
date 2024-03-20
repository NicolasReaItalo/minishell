/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:32:18 by nrea              #+#    #+#             */
/*   Updated: 2024/03/20 14:27:16 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <sys/wait.h>
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
	int		*pipes[2];
	int		nb_of_pipes;
}	t_pipes;

typedef struct s_shell
{
	t_evar	*env_vars[58]; // variables d'environnement
	t_svars	shell_vars; // variables de shell speciales
	t_pipes	pipe_array;  // pipes
	t_node	*tree; // pointeur vers le parse_tree pour le free
					//dans un subprocess en cas de builtin ou
					//d'echec de excve
}	t_shell;

void	ft_free_shell(t_shell *shell);


void	ft_exec_root(t_node *tree_root, t_shell *shell);

int ft_token_to_array(t_token **cmd_list, char	***cmd_array); ///pour test
#endif
