/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:59:14 by nrea              #+#    #+#             */
/*   Updated: 2024/03/08 13:57:15 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H
# include "token.h"
# include "libft.h"
# include "stdio.h"

t_token	*ft_get_token(t_token *stack, int rank);
int		test_ft_add_token(t_token **stack, char *content, int type);
void	*ft_free_stack(t_token **stack);
void	ft_display_stack(t_token *stack);
int		ft_stack_size(t_token *stack);
int		ft_free_token(t_token **token);
void	ft_reverse_stack(t_token **stack);
#endif
