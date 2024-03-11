/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:59:14 by nrea              #+#    #+#             */
/*   Updated: 2024/03/11 13:50:46 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_UTILS_H
# define TOKEN_UTILS_H
# include "token.h"
# include "libft.h"
# include "stdio.h"

t_token	*ft_get_token(t_token *stack, int rank);
int		ft_stack_size(t_token *stack);
int		ft_free_token(t_token **token);
void	ft_reverse_stack(t_token **stack);
void	ft_token_add_front(t_token**lst, t_token *new);
#endif
