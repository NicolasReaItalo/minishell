/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:19:14 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/15 12:59:13 by nrea             ###   ########.fr       */
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
# include "token.h"
# include "token_utils.h"
# include "libft.h"
# include "minishell_signals.h"
# include "env_variables.h"
# include "parse_execute.h"
# include "word_expansion.h"

# define OK_PROMPT "\033[3;96mminishell> \033[0m"
# define ERR_PROMPT "\033[3;96mminishell\033[1;91m(x)\033[3;96m> \033[0m"
# define D_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

int		ft_init_shell(t_shell *shell, char **envp);
char	*ft_handle_tok_err(int error);
int		evaluate(char *line, t_token **stack, t_shell *shell);
void	repl(t_shell *shell);

#endif
