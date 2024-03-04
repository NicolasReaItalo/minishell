/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:52:09 by nrea              #+#    #+#             */
/*   Updated: 2024/03/04 17:48:05 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_utils.h"
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>


//// sructure probablement a defiir dans minishell.h car elle sera utile our bcp de choses

typedef struct s_line
{
	char			*content;
	struct s_line	*next;

} t_line;

/*returns the size of a line \n and non null terminated string*/
size_t	ft_get_ret_size(char *s)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

/*returns the size of a null terminated string*/
size_t	ft_str_size(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_buffer_append(char *buf, char *line)
{
	char	*new_buf;
	int i;
	int j;

	new_buf = NULL;
	if (!buf)
	{
		buf = malloc(sizeof(char));
		if(!buf)
			return (NULL);
		buf[0] = '\0';
	}
	new_buf = malloc((ft_str_size(buf) + ft_get_ret_size(line) + 1) * sizeof(char));
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	i = 0;
	while (buf[i])
	{
		new_buf[i] = buf[i];
		i++;
	}
	j = 0;
	while (line[j] != '\n')
	{
		new_buf[i + j] = line[j];
		j++;
	}
	new_buf[i + j] = '\n';
	new_buf[i + j + 1] = '\0';
	free(buf);
	return (new_buf);
}


void	here_doc_proc(int p[2], char *eof)
{
	char	*line;


	line = NULL;
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (!ft_strncmp(line, eof, ft_str_size(eof)))
		{
			free(line);
			close(p[1]);
			exit(0);
		}
		line[ft_str_size(line)] = '\n';
		write(p[1], line, ft_str_size(line) + 1);
		free(line);
		line = NULL;
	}
	exit(0);
}


/*add a copy of line at the end of the list*/
int	ft_add_last_line(t_line **line_list, char *line)
{
	t_line	*head;
	t_line	*node;

	node = NULL;
	head = NULL;
	head = *line_list;
	node = malloc(sizeof(t_line));
	if (!node)
		return (-1);
	node->content = ft_strdup(line); // voir pb du \0
	node->next  = NULL;
	if (!*line_list)
	{
		*line_list = node;
		return (0);
	}
	while (head->next)
		head = head->next;
	head->next = node;
	return (0);
}

//read from a pipe and returns a buffer
char	*ft_read_from_pipe(int pipe[2])
{
	char	*buffer;
	char	*line;
	buffer = NULL;
	close(pipe[1]);
	while (1)
	{
		line = get_next_line(pipe[0], 0);  /// get_nextline a changer
		if (!line)
			break ;
		buffer = ft_buffer_append(buffer, line);
		free(line);
		line = NULL;
	}
		close(pipe[0]);
	return (buffer);
}

//cc -Wall -Wextra -Werror -I.. essai_here_doc.c   token_utils.c -Ilibft  -Llibft -lft -lreadline
// fonctionnne avecun leak de 1 byte, du au get_next_line ?

int	ft_fork_and_read(void)
{

	int p[2];
	int	pid;
	char	*buffer;

	if (pipe(p) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(p[0]);
		close(p[1]);
		return (-1);
	}
	if (pid == 0)
		here_doc_proc(p, "EOF");

	buffer = ft_read_from_pipe(p);
	wait(NULL);


		printf("%s", buffer);
		if (buffer)
			free (buffer);

	return (0);
}

typedef	struct s_pipe
{
	int	p[2];
	struct s_pipe *next;
} t_pipe;

/*Allocate and initiate a pipe then adds it at the end of the list*/
int	ft_add_pipe(t_pipe **pipes)
{
	t_pipe *pi;
	t_pipe *head;

	pi = NULL;
	pi = malloc(sizeof(t_pipe));
	if (!pi)
		return (-1);
	pi->next = NULL;
	if(pipe(pi->p) == -1)
	{
		free(pi);
		return (-1);
	}
	if (!*pipes)
	{
		*pipes = pi;
		return ;
	}
	head = *pipes;
	while (head->next)
		head = head->next;
	head->next = pi;
}

void ft_free_pipes(t_pipe **pipes)
{
	t_pipe	*prev;
	t_pipe	*p;

	prev = NULL;
	p = NULL;
	p = *pipes;
	while (p)
	{
		prev = p;
		p = p->next;
		free(prev);
	}
	*pipes = NULL;
}

void	ft_close_pipes_in(t_pipe *pipes)
{
	while(pipes)
	{
		close(pipes->p[1]);
		pipes = pipes->next;
	}

}
void	ft_close_pipes_out(t_pipe *pipes)
{
	while(pipes)
	{
		close(pipes->p[0]);
		pipes = pipes->next;
	}

}

t_pipe	*ft_get_pipe_by_rank(int rank,t_pipe *pipes)
{
	if (rank < 0 || !pipes)
		return (NULL);
	while (rank && pipes)
	{
		pipes = pipes->next;
		rank--;
	}
	if (rank > 0)
		return (NULL);
	return (pipes);
}

int	ft_create_heredoc_proc(int rank, t_pipe **pipes)
{
	int	pid;
	char	*buffer;
	t_pipe	*p;

	pid = fork();
	if (pid == -1)
	{
		ft_close_pipes_out(*pipes);
		ft_close_pipes_in(*pipes);
		ft_free_pipes(pipes);
		return (-1);
	}
	if (pid == 0)
	{
		p = ft_get_pipe_by_rank(rank, pipes);
		if (!p)
			return (-1);
		ft_close_pipes_out(*pipes);
		here_doc_proc(p->p, "EOF");
		ft_close_pipes_in(*pipes);
		ft_free_pipes(pipes);
		exit(0);
	}
	return (0);
}


void	ft_syntax_and_heredoc(t_token *stack)
{



}






int main()
{
	ft_fork_and_read();


	return (0);
}
