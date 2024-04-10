/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:19:14 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/10 10:32:41 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "parser.h"
# include "token.h"
# include "token_utils.h"
# include "libft.h"
# include "minishell_signals.h"
# include "env_variables.h"
# include "execution.h"
# include "word_expansion.h"

int		ft_init_shell(t_shell *shell, char **envp);
char	*ft_handle_tok_err(int error);

void	repl(t_shell *shell);

#endif
