/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:28:30 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/03 14:30:13 by tjoyeux          ###   ########.fr       */
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

// Common expansion functions
char	*find_next_param_expansion(char *str, char **next, int *in_quotes);
void	free_words_tab(char ***words);
int		match_pattern(char *pattern, char *str);
// char	*ft_concat_3str(char *first, char *second, char *third, int len);
void	unquote_content(char *content);
int		words_to_token(t_token *ptr, char **words, int i);

// Expansion of parameters
int	expanse_param(t_shell *shell, t_token *token, char *next, t_expvar *vars);
int	expanse_param_redir(t_expvar *vars, t_shell *shell, char **output, char **next);

// Expansion of pathname
int		expand_pathname_cmd(t_token *token);
char	**sort_pathname_tab(char **tab);
//int	expand_pathname_(t_token *token);

// Redir expansion



int		word_expand(t_node *node, t_shell *shell);

//int		field_splitting(t_token *token, t_shell *shell);
int		expand_param(t_shell *shell, t_token *token);
char	*expand_param_redir(char *str, t_shell *shell);
//int		field_splitting(t_token *token, t_shell *shell, char *new);
int		field_splitting(t_token *token, char *start, char *end);
int		contains_ifs(t_token *token, t_shell *shell, char *str);
//int 	expand_pathname_redir(t_token *token);
int		expand_redir(t_token *token, t_shell *shell);
//int		count_valid_pathname(char *content, t_token *token);
//int		only_stars(char *pattern);
//char	*find_next_param_expansion(char *str, char **next);
//int		ambiguous_redirect(char *content);
int		contains_ifs_redir(char *str, char *ifs);
int		pathname_in_quotes(char *content);
#endif
