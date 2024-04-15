/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/15 13:35:10 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tests.h"

void	exit_gracefully(t_shell *shell, int exit_status)
{
	ft_dprintf(2, "Exiting Minishell... See you soon!\n");
	ft_free_shell(shell);
	exit (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (set_interactive_signals() == -1)
		exit(1);
	//TODO ajouter istty pour verifier qu'on est dans un shell interactif
	//TODO voir la gestion des arguments
	//TODO voir si on exit(1) en cas de pb de malloc dans evaluate
	//TODO virer la fonction debug des builtins
	//TODO Expansion : pb de segfault sur l'unquoting avec espaces
	// echo "1 2"
	//TODO IFS : il faut que lIFS ne soit applique que si la variable expanse
	// fais partie du premier token de cmd
	//TODO : expansion voir si traitement separe dans le cas d'une erreur
	// de malloc pour word_expand, Quel code et quel comportement adopter ?

	(void) argc;
	(void) argv;
	if (!ft_init_shell(&shell, envp))
		return (1);
	if (!ft_strlen(ft_get_var_value("PATH", shell.env_vars, shell.shell_vars)))
	{
		printf("The PATH variable has not been inherited from parent\n");
		printf("Setting PATH to default value...\n");
		if (ft_set_var("PATH", D_PATH, shell.env_vars, &shell.shell_vars) != 1)
		{
			ft_dprintf(2, "PATH init Error\n");
			ft_free_shell(&shell);
			exit(1);
		}
	}
	repl(&shell);
	exit_gracefully(&shell, 0);
}
