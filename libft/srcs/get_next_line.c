/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:18:37 by nrea              #+#    #+#             */
/*   Updated: 2024/03/25 13:17:12 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	t_gnl_l			*list;
	t_gnl_l			*last_node;
	int				read_value;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	list = NULL;
	last_node = NULL;
	if (buffer[0])
		if (!ft_append_list(&list, buffer, &last_node))
			return (NULL);
	while (!ft_search_eol(last_node))
	{
		read_value = read(fd, buffer, BUFFER_SIZE);
		if (read_value == -1)
			return (ft_lstfree(&list));
		buffer[read_value] = '\0';
		if (read_value == 0)
			return (ft_assemble_line(&list, 1, buffer));
		last_node = ft_append_list(&list, buffer, &last_node);
	}
	return (ft_assemble_line(&list, 0, buffer));
}

/*Clean the linked list used create the line and copy the remainder to the
static buffer*/
void	ft_clean_list(t_gnl_l **list, char *buffer)
{
	char	*content;
	int		i;

	if (!*list || !list)
		return ;
	content = (ft_lstgetlast(*list))->content;
	while (*content && *content != '\n')
		content++;
	if (*content == '\n')
		content++;
	i = 0;
	while (content[i])
	{
		buffer[i] = content[i];
		i++;
	}
	buffer[i] = '\0';
	ft_lstfree(list);
}

/*run the list char by char and append the char to the line until \n is reached
(or /0 if the eof flags is set)*/
char	*ft_copy_line(t_gnl_l *list, char *line, int eof)
{
	int		i;
	int		j;

	if (!line)
		return (NULL);
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			line[i + j] = list->content[i];
			if (!eof)
			{
				if (list->content[i] == '\n')
					return (line);
			}
			i++;
		}
	j += i;
		list = list->next;
	}
	return (line);
}

/*malloc and assemble the line from the list*/
char	*ft_assemble_line(t_gnl_l **list, int eof, char *buffer)
{
	char	*line;
	int		line_size;

	if (!*list)
		return (NULL);
	line_size = ft_countchar(*list, eof);
	line = malloc((line_size + 1) * sizeof(char));
	if (!line)
		return (ft_lstfree(list));
	line[line_size] = '\0';
	line = ft_copy_line(*list, line, eof);
	ft_clean_list(list, buffer);
	return (line);
}

/*Run the list char by char to look for \n
return 1 on success or 0 if none was found*/
int	ft_search_eol(t_gnl_l *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}
