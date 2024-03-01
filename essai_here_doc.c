/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essai_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:52:09 by nrea              #+#    #+#             */
/*   Updated: 2024/03/01 18:54:03 by nrea             ###   ########.fr       */
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

void	here_doc_proc(int p[2], char *eof)
{
	char	*line;


	line = NULL;
	close(p[0]);
	while (1)
	{
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (!ft_strncmp(line, eof, ft_str_size(eof)))
		{
			free(line);
			close(p[1]);
			exit(0);
		}
		write(p[1], line, ft_get_ret_size(line) + 1);
		free(line);
		line = NULL;
	}
	close(p[1]);
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


//cc -Wall -Wextra -Werror -I.. essai_here_doc.c   token_utils.c -Ilibft  -Llibft -lft -lreadline
// fonctionnne avecun leak de 1 byte, du au get_next_line ?

int	ft_fork_and_read(void)
{

	int p[2];
	int	pid;
	char	*line;
	t_line	*lines;

	lines = NULL;
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
	line = NULL;
	close(p[1]);
	while (1)
	{
		line = get_next_line(p[0], 0);  /// purge ? A voir avec Thomas
		if (!line)
			break ;
		ft_add_last_line(&lines, line);
		free(line);
		line = NULL;
	}
	close(p[0]);
	waitpid(pid, NULL, 0);

	t_line *lines_to_read;

	lines_to_read = lines;
	while (lines_to_read)
	{
		printf("%s", lines_to_read->content);
		lines_to_read = lines_to_read->next;
	}

	t_line *cur;
	while (lines)
	{
		free(lines->content);
		cur = lines;
		lines = lines->next;
		free(cur);
	}


	return (0);
}


int main()
{
	ft_fork_and_read();


	return (0);
}
