/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:15:43 by nrea              #+#    #+#             */
/*   Updated: 2024/04/02 13:26:57 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	get_directory(char *buffer, int buffer_size)
{
	buffer = malloc(buffer_size * sizeof(char));
	if (buffer == NULL)
	{
		write(2, "pwd: Internal Error\n", 21);
		return (1);
	}
	ft_memset(buffer, 0, buffer_size * sizeof(char));
	if (getcwd(buffer, buffer_size) == NULL)
	{
		free(buffer);
		if (errno == ERANGE && buffer_size <= 900)
			return (get_directory(buffer, buffer_size * 2));
		else
		{
			perror("pwd");
			return (1);
		}
	}
	ft_dprintf(1, "%s\n", buffer);
	free(buffer);
	return (0);
}

/*Builtin: print name of current/working directory*/
int	pwd(t_token *cmd)
{
	char		*buffer;
	int			buffer_size;

	(void) cmd;
	buffer = NULL;
	buffer_size = 100;
	if (get_directory(buffer, buffer_size) == 1)
		return (1);
	return (0);
}
