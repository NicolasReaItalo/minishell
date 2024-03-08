/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:58:13 by nrea              #+#    #+#             */
/*   Updated: 2024/03/08 12:43:50 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_utils.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/*returns the size of a line \n and non null terminated string*/
static size_t	ft_get_ret_size(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static void	ft_cpy_buf(char *buf, char *line, char *new_buf)
{
	int	i;
	int	j;

	i = 0;
	while (buf[i])
	{
		new_buf[i] = buf[i];
		i++;
	}
	if (i != 0)
	{
		new_buf[i] = '\n';
		i++;
	}
	j = 0;
	while (line[j])
	{
		new_buf[i + j] = line[j];
		j++;
	}
	new_buf[i + j] = '\0';
}

static char	*ft_buffer_append(char *buf, char *line)
{
	char	*new_buf;

	new_buf = NULL;
	if (!buf)
	{
		buf = malloc(sizeof(char));
		if (!buf)
			return (NULL);
		buf[0] = '\0';
	}
	new_buf = malloc((ft_strlen(buf) + ft_strlen(line) + 1) * sizeof(char));
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	ft_cpy_buf(buf, line, new_buf);
	free(buf);
	return (new_buf);
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
	tok->content = NULL;
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!ft_strncmp(line, eof, sizeof(eof)))
		{
			free(line);
			if (!tok->content)
				tok->content = ft_strdup("");
			break ;
		}
		tok->content = ft_buffer_append(tok->content, line);
		free(line);
	}
	return (0);
}
