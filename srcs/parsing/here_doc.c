/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:58:13 by nrea              #+#    #+#             */
/*   Updated: 2024/04/30 10:34:01 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_utils.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "parse_execute.h"
#include <termios.h>

/*appends the  line read at the end of the content*/
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

static void	treat_line(int fd[2], char *end, char *line)
{
	int	len;

	if (!line)
	{
		close(fd[1]);
		exit(0);
	}
	len = ft_strlen(line);
	if (len && !ft_strncmp(line, end, len))
	{
		free(line);
		close(fd[1]);
		exit(0);
	}
	write(fd[1], line, strlen(line));
	write(fd[1], "\n", 1);
	free(line);
}

void	child_hd(char *eof, int fd[2], t_shell *shell, t_token **stack)
{
	char	*line;
	char	end[10000];

	close(fd[0]);
	ft_memset(end, 0, 10000);
	if (ft_strcpy(end, eof) == NULL)
	{
		close(fd[1]);
		exit(1);
	}
	if (set_hd_child_signals() == -1)
		exit(1);
	ft_free_shell(shell);
	kill_stack(stack);
	while (1)
	{
		line = NULL;
		line = readline(">");
		treat_line(fd, end, line);
	}
	close(fd[1]);
	exit(0);
}

int	read_from_child(t_token *tok, int fd[2])
{
	char	buf[2];

	ft_memset(buf, 0, 2);
	free(tok->content);
	tok->content = ft_strdup("");
	if (!tok->content)
		return (1);
	while (read(fd[0], buf, 1) > 0)
	{
		if (ft_append(&tok->content, buf) == -1)
		{
			close(fd[0]);
			wait(NULL);
			return (1);
		}
	}
	return (0);
}

/*fill the buffer with the user input
0 success
1 error
130 sigint
*/
int	get_hd(t_token *tok, char *eof, t_shell *shell, t_token **stack)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (set_hd_parent_signals() == -1)
		return (1);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	if (pid == 0)
		child_hd(eof, fd, shell, stack);
	close(fd[1]);
	if (read_from_child(tok, fd))
		return (1);
	close(fd[0]);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
