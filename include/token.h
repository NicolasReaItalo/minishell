/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:08:35 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/08 13:21:04 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

# define PIPE 1 // "|"
# define AND 2 // "&&"
# define OR 3 // "||"
# define R_IN 4 // "<"
# define R_OUT 5 // ">"
# define R_APPEND 6 // ">>"
# define R_HEREDOC 7 // "<<"
# define O_BRACKET 8 // "("
# define C_BRACKET 9 // ")"
# define WORD 0 // Tout le reste

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;
typedef struct	s_syntax_rule
{
	int	token;
	int	valid_next[10];
	int valid_prev[10];
}				t_syntax_rule;
// TODO:Certaines fonctions font doublons...choisir!

t_token	*ft_get_token(t_token *stack, int rank);
// int		test_ft_add_token(t_token **stack, char *content, int type);
// void	*ft_free_stack(t_token **stack);
void	ft_display_stack(t_token *stack);
int		ft_stack_size(t_token *stack);
int		ft_free_token(t_token **token);
void	ft_reverse_stack(t_token **stack);
int		check_syntax(t_token *stack);
#endif
