/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:47:22 by nrea              #+#    #+#             */
/*   Updated: 2024/05/07 14:28:40 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"
#include "word_expansion.h"
#include <readline/readline.h>
#include <readline/history.h>
/*Delete a token in double linked stack*/
void	ft_delete_token(t_token **token, t_token **stack)
{
	t_token	*prev;
	t_token	*next;

	if (!*token)
		return ;
	prev = (*token)->prev;
	next = (*token)->next;
	if (prev)
		prev->next = next;
	else
		*stack = next;
	if (next)
		next->prev = prev;
	free((*token)->content);
	free(*token);
	*token = NULL;
}

/*destroys the words once their content is used by redirections*/
static int	ft_clean_words(t_token **stack)
{
	t_token	*tok;
	t_token	*prev;

	tok = ft_get_token(*stack, -1);
	if (!tok)
		return (-1);
	while (tok)
	{
		if (tok->type >= 4 && tok->type <= 7)
		{
			prev = tok->prev;
			ft_delete_token(&prev, stack);
		}
		tok = tok->prev;
	}
	return (0);
}

int	manage_heredoc(t_token	*tok, t_token **stack, t_shell *shell)
{
	int		ret;
	t_token	*prev_tok;

	prev_tok = tok->prev;
	if (contains_quotes(prev_tok->content) == 1)
		tok->heredoc_quoted = 1;
	unquote_content(prev_tok->content);
	ret = get_hd(tok, prev_tok->content, shell, stack);
	if (set_interactive_signals() == -1)
		return (1);
	if (ret != 0)
	{
		ft_set_exit_status(ret, &shell->shell_vars);
		return (ret);
	}
	return (0);
}

/*for < > and >> copy the content of the word
token containing the filename for redir*/
static int	manage_classic_redir(t_token *tok)
{
	t_token	*prev_tok;

	free(tok->content);
	prev_tok = tok->prev;
	tok->content = ft_strdup(prev_tok->content);
	if (!tok->content)
		return (-1);
	return (0);
}

/*
Parcours la satck de la fin au debut
si <<, capture le heredoc et le EOF puis stocke le buffer dans token.content
supprime le token word suivant
si <,stocke le content du token suivant comme fichier de redirection
si >,stocke le content du token suivant comme fichier de redirection
supprime le token word suivant
si >>,stocke le content du token suivant comme fichier de redirection
*/
int	ft_redirections(t_token **stack)
{
	t_token	*tok;
	int		ret;

	if (!*stack)
		return (-1);
	tok = ft_get_token(*stack, -1);
	while (tok)
	{
		if (tok->type >= R_IN && tok->type <= R_APPEND)
		{
			ret = manage_classic_redir(tok);
			if (ret)
				return (ret);
		}
		tok = tok->prev;
	}
	return (ft_clean_words(stack));
}
