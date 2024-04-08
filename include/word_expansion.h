/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyeux <joyeux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:28:30 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/09 00:15:24 by joyeux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_H
# define WORD_EXPANSION_H
# include <dirent.h>
# include "libft.h"
# include "parser.h"
# include "env_variables.h"
# include "minishell.h"

int		field_splitting(t_token *token, t_shell *shell);
char	*expand_param(char *str, t_shell *shell);
char	*expand_param_redir(char *str, t_shell *shell);
int		words_to_token(t_token **ptr, char **words);
int		field_splitting(t_token *token, t_shell *shell);
//int		contains_ifs(t_token *token, t_shell *shell);
void	free_words_tab(char ***words);
int		expand_pathname_cmd(t_token *token, int *count);
int 	expand_pathname_redir(t_token *token);
int		count_valid_pathname(char *content, t_token *token);
int		match_pattern(char *pattern, char *str);
//char	*find_next_param_expansion(char *str, char **next);
//char	*ft_concat_3str(char *first, char *second, char *third);

#endif
