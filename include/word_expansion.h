/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyeux <joyeux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:28:30 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/30 00:52:15 by joyeux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_H
# define WORD_EXPANSION_H
# include <dirent.h>
# include "libft.h"
# include "parse_execute.h"
# include "env_variables.h"

int		word_expand(t_node *node, t_shell *shell);

//int		field_splitting(t_token *token, t_shell *shell);
int		expand_param(t_shell *shell, t_token *token);
char	*expand_param_redir(char *str, t_shell *shell);
int		words_to_token(t_token *ptr, char **words);
//int		field_splitting(t_token *token, t_shell *shell, char *new);
int		field_splitting(t_token *token, char *new, char *start, char *end);
int		contains_ifs(t_token *token, t_shell *shell, char *str);
void	free_words_tab(char ***words);
int		expand_pathname_cmd(t_token *token);
//int 	expand_pathname_redir(t_token *token);
int		expand_redir(t_token *token, t_shell *shell);
int		count_valid_pathname(char *content, t_token *token);
int		only_stars(char *pattern);
int		match_pattern(char *pattern, char *str);
//char	*find_next_param_expansion(char *str, char **next);
//char	*ft_concat_3str(char *first, char *second, char *third);
//int		ambiguous_redirect(char *content);
int		contains_ifs_redir(char *str, char *ifs);
int		pathname_in_quotes(char *content);
void	unquote_content(char *content);
#endif
