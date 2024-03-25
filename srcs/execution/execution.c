/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:31:47 by nrea              #+#    #+#             */
/*   Updated: 2024/03/25 17:51:31 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*execute a node (pipe or exec) in a child process and return the exit status
returns -1 in case of failure*/
int	ft_exec_in_fork(t_node *node, int pipe_nb, t_shell *shell)
{
	int	exit_status;
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		if (node->type == N_PIPE)
			ft_exec_pipe(node, pipe_nb, shell);
		else if (node->type == N_EXEC)
			ft_exec(node, pipe_nb, shell);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		return (WEXITSTATUS(exit_status));
	}
	return (0);
}

void	ft_exec_pipe(t_node *node, int pipe_nb, t_shell *shell)
{
	int	exit_status;
	int	pids[2];


	exit_status = 0;
	// SI pipe_nb == 0 // on est donc le premier pipe on va initialiser le tableau de pipes
	if (pipe_nb == 0) // on est au premier pipe
	{
		if (ft_create_pipe_array(node, shell) == -1)
		{
			write(2, "Error during pipe initialisation\n", 34);
			exit (1);
		}
		if (ft_initialize_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes) == -1)
		{
			write(2, "Error during pipe initialisation\n", 34);
			ft_free_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
			exit (1);
		}
	}
	pids[0] = fork();
	if (pids[0] == -1)
	{
		exit (1); // Ajouter le free pour quitter proprement;
	}
	if (pids[0] == 0)
	{
		if (node->left->type == N_PIPE)
			ft_exec_pipe(node->left, pipe_nb + 1, shell);
		else if (node->left->type == N_EXEC)
		{
			node->left->side = left;
			ft_exec(node->left, pipe_nb, shell);
		}
	}
	pids[1] = fork();
	if (pids[1] == -1)
	{
		exit (1); // Ajouter le free pour quitter proprement;
	}
	if (pids[1] == 0) // lenode.right ne peut etre qu'un exec
	{
		node->right->side = right;
		ft_exec(node->right, pipe_nb, shell);
	}
	ft_close_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
	ft_free_pipe_array(shell->pipe_array.pipes, shell->pipe_array.nb_of_pipes);
	ft_free_shell(shell);
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}


void	ft_exec_root(t_node *tree_root, t_shell *shell)
{
	int	exit_status;

	if (tree_root->type == N_EXEC) // tree = un seul node EXEC
	{
		//expansion du node et detection builtin a ajouter
		if (!tree_root->is_builtin)
		{
			exit_status = ft_exec_in_fork(tree_root, -1,  shell);
			// if (exit_status != 0)
			// 	ft_dprintf(2, "Internal Error !");  // gestion erreur a affiner pour detecter une erreur fork malloc etc...

			ft_set_exit_status(exit_status, &shell->shell_vars);
		}
		else
		{
			// execution builtin dans le processus principal
		}
	}
	else if (tree_root->type == N_PIPE) //pipe potentiellement plusieurs pipes a la suite
		exit_status = ft_exec_in_fork(tree_root, 0,  shell);
	ft_set_exit_status(exit_status, &shell->shell_vars);
}



/*
/
nrea@paul-f5Br6s3:/$ sleep 30
^\Quit (core dumped)
nrea@paul-f5Br6s3:/$ sleep 30
^C
nrea@paul-f5Br6s3:/$ sleep 30
^\Quit (core dumped)
nrea@paul-f5Br6s3:/$ echo $?
131
nrea@paul-f5Br6s3:/$ sleep 30
^C
nrea@paul-f5Br6s3:/$ echo $?
130
nrea@paul-f5Br6s3:/$




*/




/*Create initialize and append a new pipe object
 return values : 1 -> success
				 -1 -> malloc error
				 0 -> pipe initialisation error
 */
// int	ft_append_pipe(t_pipe **pipe_queue)
// {
// 	t_pipe *new_p;
// 	t_pipe *last;

// 	new_p = malloc(sizeof(pipe));
// 	if (!new_p)
// 		return (0);
// 	new_p->next =NULL;
// 	if (pipe(new_p->p) == -1)
// 		return (0);
// 	if (*pipe_queue)
// 	{
// 		last = ft_get_last_pipe(*pipe_queue);
// 		last->next = new_p;
// 	}
// 	else
// 		*pipe_queue = new_p;
// 	return (1);
// }


/*

int	ft_execute_pipe(node ,int pipe_nb,  shell)
int	ft_execute_exec(node ,int pipe_nb,int side,  shell)



EXECUTION D'UN NODE EXEC
{

**************************************
DETERMINATION DES REDIECTIONS DE PIPES
**************************************

SI PIPE_QUEUE est vide / pipe_nb passee en param est egal a -1  ==> pas de redirection

===============
SI SIDE = LEFT
===============

**determination du OUT

SI pipe_nb >= 0
	alors dup2(get_pipe(pipe_nb).in, STDOUT) // cas simple on comunique avec la cmd a droite du pipe

**determination du IN
Pas de redirection de pipe a faire car il ne peut pas y avoir de node plus a gauche
close(get_pipe(pipe_nb).in)


==============
SI SIDE = RIGHT
==============


**determination du OUT
SI pipe_nb > 0
	alors dup2(get_pipe(pipe_nb - 1).in, STDOUT)
SINON
	pipe_nb est egal a 0 ou -1: pas de redirection a faire/on est dans le cas du node le + a droite
	close(get_pipe(pipe_nb).out)


**determination du IN

SI pipe_nb < pipe_max
	alors dup2(get_pipe(pipe_nb), STDIN)







}




tous les  odes pipes sont executes dans un fork()
EXECUTION D'UN NODE PIPE (int	ft_execute_pipe(node, int pipe_nb, shell))
{


	// SI pipe_nb == 0 // on est donc le premier pipe on va initialiser le tableau de pipes
	// // on commence par les compter
	// pipes_nb = ft_count_pipes(node)
	// on allocate et initialise le tableau de pipes

	// on incremente pipe_nb;
	// 	pid[0] = fork()
	// 		si child :	ft_execute(node.left,pipe_nb,LEFT,shell)
	// 	pid[1] = fork()
	// 		si child :	ft_execute_exec(node.right,pipe_nb,RIGHT ,  shell)
	// 	close(pipes)
	// 	free(pipes)
	// 	waitpid(pid[0], NULL)
	// 	waitpid(pid[1], &EXIT_STATUS) -> on recupere l'exit status dans ret_value
	// SI pipe_nb == 0 (on est le node le plus  droite)
	// 	shell.exit-status = EXIT_STATUS


}



EXEC_AND(node)
{
	si node.left == AND
		EXEC_AND(node.left)
	si nde.left == OR
		EXEC_OR(node.left)
	si node.left == PIPE
		exit_status = execute_in_fork(node.left)
	si node.left== EXEC
	{
		expansion(node.left)
		si node.right == builtin
		{
			applique redirections
			exit_status = execute builtin
			restaure file descriptors
		}
		sinon
			exit_status = execute_in_fork(node.left)

		met a jour EXIT STATUS
	}
	SI EXIT STATUS = 0
		si node.right == AND
			EXEC_AND(node.left)
		si nde.right == OR
			EXEC_OR(node.left)
		si node.right == PIPE
			EXEC_PIPE(node.left)
		si node.right == EXEC
		{
			expansion(node.right)
			si node.right == builtin
			{
				applique redirections
				exit_status = execute builtin
				restaure file descriptors
			}
			sinon
				exit_status = execute_in_fork(node.left)

			met a jour EXIT STATUS
		}
}


EXEC_OR(node)
{
	si node.left == AND
		EXEC_AND(node.left)
	si nde.left == OR
		EXEC_OR(node.left)
	si node.left == PIPE
		EXEC_PIPE(node.left)
	si node.left== EXEC
	{
		expansion(node.left)
		si node.right == builtin
		{
			applique redirections
			exit_status = execute builtin
			restaure file descriptors
		}
		sinon
			exit_status = execute_in_fork(node.left)

		met a jour EXIT STATUS
	}
	SI EXIT STATUS != 0
		si node.right == AND
			EXEC_AND(node.left)
		si nde.right == OR
			EXEC_OR(node.left)
		si node.right == PIPE
			EXEC_PIPE(node.left)
		si node.right == EXEC
		{
			expansion(node.right)
			si node.right == builtin
			{
				applique redirections
				exit_status = execute builtin
				restaure file descriptors
			}
			sinon
				exit_status = execute_in_fork(node.left)

			met a jour EXIT STATUS
		}
}



int	EXECUTE_IN_FORK(node)
{
	int pid;
	int exit_status;
	pid = fork()
	if pid == 0
		execute(node)
	else
		waitpid(pid, &exit_status);
	return(exit_status)
}








EXEC_ROOT(tree)
{
	si node == PIPE
		exec_pipe(node, -1, shell)
	si node == ET
		exec_AND(node, shell)
	si node == OR
		exec_or(node, shell)
	si node == EXEC
	{
		expansion(node)
		si node == builtin
		{
			applique redirections
			exit_status = execute builtin
			restaure file descriptors
		}
		sinon
			exit_status = execute_in_fork(node)

		met a jourl'exit status
	}

}


*/
