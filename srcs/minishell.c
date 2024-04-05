/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/05 14:40:04 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	if (!ft_init_shell(&shell, envp))
		return (1);
	repl(&shell);
	ft_dprintf(2, "\nMinishell has exited due to an internal error\n");
	ft_free_shell(&shell);
	return (1);
}
