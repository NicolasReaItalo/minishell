/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:28:30 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/11 18:41:17 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_H
# define WORD_EXPANSION_H
# include <dirent.h>
# include "libft.h"
# include "parse_execute.h"
# include "env_variables.h"

int		field_splitting(t_token *token, t_shell *shell);
char	*expand_param(char *str, t_shell *shell);
int		words_to_token(t_token **ptr, char **words);
int		field_splitting(t_token *token, t_shell *shell);
void	free_words_tab(char ***words);
int		expand_pathname_cmd(t_token *token);
int 	expand_pathname_redir(t_token *token);
#endif
