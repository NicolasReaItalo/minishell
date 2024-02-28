/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:43:49 by nrea              #+#    #+#             */
/*   Updated: 2024/02/28 14:24:09 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"
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
			t_token			*redir;
			t_token			*cmd;
			char			*hd_buffer;
		};
		struct
		{
			struct s_node	*left;
			struct s_node	*right;
		};
	};
}			t_node;
#endif
