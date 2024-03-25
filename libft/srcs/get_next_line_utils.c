/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:55:45 by nrea              #+#    #+#             */
/*   Updated: 2024/03/25 13:17:12 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*malloc a NULL terminated string from string s*/
// char	*ft_strdup(const char *s)
// {
// 	size_t	s_size;
// 	char	*dup;
// 	int		i;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	s_size = 0;
// 	while (s[s_size])
// 		s_size++;
// 	dup = malloc((s_size + 1) * sizeof(char));
// 	if (!dup)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }

/*Returns the last node of the list.*/
t_gnl_l	*ft_lstgetlast(t_gnl_l *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*Create a node  with node->content = content
append the node at the end of the list if it exist or assign node to list
return the node create and assign the las_node pointer to it ( to save lines)*/
t_gnl_l	*ft_append_list(t_gnl_l **list, char *content, t_gnl_l **last_node)
{
	t_gnl_l	*node;

	node = malloc(sizeof(t_gnl_l));
	if (!node)
		return (NULL);
	node->content = ft_strdup(content);
	if (!node->content)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	if (*list)
	{
		(ft_lstgetlast(*list))->next = node;
	}
	else
		*list = node;
	*last_node = node;
	return (node);
}

/*free all the nodes and content in a list*/
void	*ft_lstfree(t_gnl_l **lst)
{
	t_gnl_l	*p;
	t_gnl_l	*p2;

	if (!lst)
		return (NULL);
	p = *lst;
	*lst = NULL;
	while (p)
	{
		if (p->content)
			free(p->content);
		p2 = p;
		p = p->next;
		free(p2);
	}
	return (NULL);
}

/*parse the list content until \n or until the end of the list if eof is set
 and calculate the nbr of characters needed to malloc
 Does not count the NULL character*/
int	ft_countchar(t_gnl_l *list, int eof)
{
	int	count;
	int	i;

	count = 0;
	while (list)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			count++;
			if (!eof)
			{
				if (list->content[i] == '\n')
					return (count);
			}
			i++;
		}
		list = list->next;
	}
	return (count);
}
