/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:47:22 by nrea              #+#    #+#             */
/*   Updated: 2024/03/08 13:31:28 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
void	ft_clean_words(t_token **stack)
{
	t_token	*tok;
	t_token	*prev;

	tok = ft_get_token(*stack, -1);
	if (!tok)
		return ;
	while (tok)
	{
		if (tok->type >= 4 && tok->type <= 7)
		{
			prev = tok->prev;
			ft_delete_token(&prev, stack);
		}
		tok = tok->prev;
	}
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
	t_token	*prev_tok;

	if (!*stack)
		return (-1);
	tok = ft_get_token(*stack, -1);
	while (tok)
	{
		if (tok->type == R_HEREDOC)
		{
			prev_tok = tok->prev;
			ft_capture_here_doc(tok, prev_tok->content);
		}
		else if (tok->type >= 4 && tok->type <= 6)
		{
			free(tok->content);
			prev_tok = tok->prev;
			tok->content = ft_strdup(prev_tok->content);
		}
		tok = tok->prev;
	}
	ft_clean_words(stack);
	return (0);
}
