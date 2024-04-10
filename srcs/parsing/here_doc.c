/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:58:13 by nrea              #+#    #+#             */
/*   Updated: 2024/04/10 18:02:15 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_utils.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "parser.h"




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



void	child_hd(char *eof, int fd[2], t_shell *shell)
{
	char	*line;
	if (set_hd_child_signals() == -1)
		exit(1);
	close(fd[0]);
	ft_free_shell(shell);
	while(1)
	{
		line = NULL;
		line = readline(">");
		if (!line )
		{
			close(fd[0]);
			exit(0);
		}
		if (!strcmp(line, eof))
		{
			free(line);
			close(fd[1]);
			exit(0);
		}
		else
		{
			write(fd[1], line, strlen(line));
			write(fd[1], "\n", 1);
		}
	}
		exit(0);
}

int ret_error(int fd[2])
{
	close(fd[0]);
	wait(NULL);
	return (1);
}

/*fill the buffer with the user input
0 success
1 error
130 sigint
*/
int	ft_capture_here_doc(t_token *tok, char *eof, t_shell *shell)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	char	buf[2];

	if (set_hd_parent_signals() == -1)
		return (1);
	ft_memset(buf, 0, 2);
	free(tok->content);
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
		child_hd(eof, fd, shell);
	tok->content = ft_strdup("");
	if (!tok->content)
		return (1);
	close(fd[1]);
	while(read(fd[0], buf, 1) > 0)
	{
		if (ft_append(&tok->content, buf) == -1)
			return (ret_error(fd));
	}
	close(fd[0]);
	waitpid(pid, &status, 0);
	return ( WEXITSTATUS(status));
}
