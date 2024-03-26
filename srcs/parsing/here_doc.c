/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:58:13 by nrea              #+#    #+#             */
/*   Updated: 2024/03/25 14:17:31 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_utils.h"

/*appends the read line atthe end of the content*/
int	ft_append(char **content, char *line)
{
	char	*buf;

	buf = NULL;
	buf = ft_strjoin(*content, line);
	if (!buf)
		return (-1);
	free (*content);
	*content = buf;
	return (0);
}

/*the EOF has been detected we exit cleanly*/
int	ft_return_safe(char *line)
{
	free(line);
	return (0);
}

/*Starts a readline loop to capture the user input and stores it
 in a buffer in the content of the token*/
int	ft_capture_here_doc(t_token *tok, char *eof)
{
	char	*line;

	if (!tok || tok->type != R_HEREDOC || !eof)
		return (-1);
	line = NULL;
	free(tok->content);
	tok->content = ft_strdup("");
	if (!tok->content)
		return (1);
	while (1)
	{
		write(1, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, eof, ft_strlen(eof)))
			return (ft_return_safe(line));
		if (ft_append(&tok->content, line) == -1)
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}
