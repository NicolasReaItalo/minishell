/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:19:14 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/18 13:55:21 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "parser.h"
# include "token.h"
# include "token_utils.h"
# include "libft.h"
# include "env_variables.h"

typedef struct	s_shell
{
	t_evar	*env_vars[58];
	t_evar	shell_vars;
}	t_shell;
#endif
