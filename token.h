/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:08:35 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/02/27 15:08:43 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <stdlib.h>

# define PIPE 1
# define AND 2
# define OR 3
# define R_IN 4
# define R_OUT 5
# define R_APPEND 6
# define R_HEREDOC 7
# define WORD 8
# define O_BRACKET 9
# define C_BRACKET 10

typedef struct	s_token
{
	int				type;
	char 			*content;
	struct s_token	*next;
}				t_token;
#endif