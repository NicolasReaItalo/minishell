/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expansion_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:28:15 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/07 16:42:27 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

int	contains_ifs_redir(char *str, char *ifs)
{
	while (*str)
	{
		if (ft_strchr(ifs, *str))
			return (1);
		str++;
	}
	return (0);
}

// expand the redir token
//	- strip the string from ifs
//	- si empty => error `$VAR: ambiguous redirect `
//	- strchr ifs => error
//	- si strchr *
//    	- count valid_pathnames si > 1 =>error
//    	- expand
// return an error code
int	ambiguous_redirect(char *content)
{
	ft_putstr_fd(content, 2);
	ft_putstr_fd(": ambiguous redirect\n ", 2);
	return (5);
}

void	files_found(t_token *token, char **tmp_name)
{
	if (token->nb_files == 1)
	{
		free(token->content);
		token->content = *tmp_name;
	}
	else
		free(*tmp_name);
}

int	expand_here_doc(t_token *token, t_shell *shell)
{
	char	*str;

	if (token->heredoc_quoted == 1)
		return (0);
	str = expand_param_redir_heredoc(token->content, shell);
	if (!str)
		return (1);
	free (token->content);
	token->content = str;
	return (0);
}
