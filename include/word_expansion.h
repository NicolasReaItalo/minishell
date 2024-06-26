/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:41:16 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/07 16:42:58 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_EXPANSION_H
# define WORD_EXPANSION_H
# include <dirent.h>
# include "libft.h"
# include "parse_execute.h"
# include "env_variables.h"

typedef struct s_expvar
{
	char	*key;
	char	*ifs;
	int		index;
	char	*next;
	int		in_quotes;
	char	*new;
}				t_expvar;

int		word_expand(t_node *node, t_shell *shell);

// Common expansion functions
char	*find_next_param_expansion(char *str, char **next, int *in_quotes);
void	free_words_tab(char ***words);
int		match_pattern(char *pattern, char *str);
char	*requote_param_expansion(char *str);
char	*unquote_content(char *content);
int		words_to_token(t_token *ptr, char **words, int i);

// Expansion of parameters
int		expand_param(t_shell *shell, t_token *token);
int		expanse_param(t_shell *shell, t_token *token, char *next,
			t_expvar *vars);
int		expanse_param_redir(t_expvar *vars, t_shell *shell, char **output,
			char **next);
char	*dollar_sign(char **str, char **next, int *len);

// IFS
int		field_splitting(t_token *token, char *start, char *end);
int		contains_ifs(t_token *token, t_shell *shell, char *str);
int		contains_ifs_redir(char *str, char *ifs);

// Expansion of pathname
int		expand_pathname_cmd(t_token *token);
char	**sort_pathname_tab(char **tab);
int		pathname_in_quotes(char *content);

// Redir expansion
int		redir_exp(t_token *token, t_shell *shell);
int		expand_redir(t_token *token, t_shell *shell);
char	*expand_param_redir(char *str, t_shell *shell);
int		expand_here_doc(t_token *token, t_shell *shell);
int		ambiguous_redirect(char *content);
void	files_found(t_token *token, char **tmp_name);
int		expand_here_doc(t_token *token, t_shell *shell);
int		is_valid_param_char(char c);
int		is_valid_first_param_char(char c);
int		unimplemented_special_var(char c);
char	*expand_param_redir_heredoc(char *str, t_shell *shell);
#endif
