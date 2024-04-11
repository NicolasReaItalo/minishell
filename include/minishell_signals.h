/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signals.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:50 by nrea              #+#    #+#             */
/*   Updated: 2024/04/11 18:54:38 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNALS_H
# define MINISHELL_SIGNALS_H
# include "minishell_signals.h"
# include <signal.h>

extern volatile sig_atomic_t	g_sig;
int	set_interactive_signals(void);
int	set_hd_child_signals(void);
int	set_hd_parent_signals(void);
int	set_exec_signals(void);
#endif
