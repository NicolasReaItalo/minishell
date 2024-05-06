/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:15:43 by nrea              #+#    #+#             */
/*   Updated: 2024/05/06 15:17:00 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"
#include <linux/limits.h>

/*Builtin: print name of current/working directory*/
int	pwd(t_token *cmd, t_node *node, t_shell *shell)
{
	char		*buffer;

	(void) cmd;
	(void) shell;
	(void) node;
	buffer = NULL;
	buffer = malloc(PATH_MAX * sizeof(char));
	if (buffer == NULL)
	{
		write(2, "pwd: Internal Error\n", 21);
		return (1);
	}
	ft_memset(buffer, 0, PATH_MAX * sizeof(char));
	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		free(buffer);
		perror("pwd");
		return (1);
	}
	if (write(1, buffer, ft_strlen(buffer)) < 0)
		return (free(buffer), write_error("pwd", 1));
	if (write(1, "\n", 1) < 0)
		return (free(buffer), write_error("pwd", 1));
	free(buffer);
	return (0);
}
