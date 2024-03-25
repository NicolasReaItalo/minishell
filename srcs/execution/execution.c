/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:31:47 by nrea              #+#    #+#             */
/*   Updated: 2024/03/25 11:09:22 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/stat.h>



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


	SI pipe_nb = -1 // on est donc le premier pipe on va initialiser le tableau de pipes
	// on commence par les compter
	pipes_nb = ft_count_pipes(node)
	on allocate et initialise le tableau de pipes

	on incremente pipe_nb;
		pid[0] = fork()
			si child :	ft_execute(node.left,pipe_nb,LEFT,shell)
		pid[1] = fork()
			si child :	ft_execute_exec(node.right,pipe_nb,RIGHT ,  shell)
		close(pipes)
		free(pipes)
		waitpid(pid[0], NULL)
		waitpid(pid[1], &EXIT_STATUS) -> on recupere l'exit status dans ret_value
	SI pipe_nb == 0 (on est le node le plus  droite)
		shell.exit-status = EXIT_STATUS


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
//parcours node.left en comptant le nobre de pipes
int ft_count_pipes(t_node *node)
{
	if (node->type == N_PIPE)
		return(1 + ft_count_pipes(node->left));
	return (0);
}








void	ft_exec_pipe(t_node *node, int pipe_nb, t_shell *shell)
{
	(void) node;
	(void) pipe_nb;
	(void) shell;
//// A ecrire...
	return ;
}













/*convert the cmd list to an array** of char* with every token content
 initialise the cmd_array passed in parameter
return 1 in case of success, 0 otherwise
*/
int ft_token_to_array(t_token **cmd_list, char	***cmd_array)
{
	int		size;
	int		i;
	t_token	*node;

	size = ft_stack_size(*cmd_list);
	*cmd_array = (char **) malloc((size + 1) * sizeof(char *));
	if (!*cmd_array)
		return (0);
	node = *cmd_list;
	i = 0;
	while (node)
	{
		(*cmd_array)[i] = ft_strdup(node->content);
		if (!(*cmd_array)[i])
		{
			ft_free_splitted(*cmd_array);
			return (0);
		}
		i++;
		node = node->next;
	}
	(*cmd_array)[i] = NULL;
	kill_stack(cmd_list);
	return (1);
}

int	ft_malloc_error(void)
{
	write(2, "Error during malloc\n", 21);
	return (1);
}

int	ft_cmd_not_found_error(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	return (127);
}
int	ft_cmd_forbidden(char *cmd)
{
	perror(cmd);
	return (126);
}

char	*ft_join_paths(char const *path, char const *cmd)
{
	char	*full_path;
	int		i;
	int		j;

	if (!path || !cmd)
		return (NULL);
	full_path = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!full_path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		full_path[i] = path[i];
		i++;
	}
	full_path[i] = '/';
	i++;
	j = 0;
	while (cmd[j])
	{
		full_path[i + j] = cmd[j];
		j++;
	}
	full_path[i + j] = '\0';

	return (full_path);
}


int ft_get_full_cmd(char **full_cmd , char *content, t_shell *shell)
{
	char	**paths;
	int		i;
	char	*var_path;

	var_path = ft_get_var_value("PATH", shell->env_vars, shell->shell_vars);
	paths = ft_split(var_path, ':');

	i = 0;
	while (paths[i])
	{
		*full_cmd = NULL;
		*full_cmd =	ft_join_paths(paths[i], content);
		if (!full_cmd)
			return (ft_malloc_error());
		if (access(*full_cmd, F_OK) == 0)
			return (0);
		free(*full_cmd);
		i++;
	}
	ft_free_splitted(paths);
	return (ft_cmd_not_found_error(content));
}

/*Apply the redirection of the outfile in TRUNC_MODE
	return 0 in case of success or the error code to output 1 */
int	ft_apply_r_out(char *file)
{
int	out_file;

out_file = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
if (out_file == -1)
{
	perror(file);
	return(1);
}
if (dup2(out_file, STDOUT_FILENO) == -1)
{
	close(out_file);
	return(1);
}
	close(out_file);
	return (0);
}
/*Apply the redirection of the outfile in APPEND_MODE
	return 0 in case of success or the error code to output 1 */
int	ft_apply_r_append(char *file)
{
int	out_file;

out_file = open(file, O_CREAT | O_APPEND | O_WRONLY, 0666);
if (out_file == -1)
{
	perror(file);
	return(1);
}
if (dup2(out_file, STDOUT_FILENO) == -1)
{
	close(out_file);
	return(1);
}
	close(out_file);
	return (0);
}

/*Apply the redirection of the infile
	return 0 in case of success or the error code to output : 1 */
int	ft_apply_r_in(char *file)
{
int	in_file;

in_file = open(file, O_RDONLY);
if (in_file == -1)
{
	perror(file);
	return(1);
}
if (dup2(in_file, STDIN_FILENO) == -1)
{
	close(in_file);
	return(1);
}
	close(in_file);
	return (0);
}


char    *ft_strcpy(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

static void	ft_putnbr_base_l(unsigned long nbr, char *base, char *file )
{
	unsigned long	base_len;
	unsigned long	tmp;
	unsigned long	div_value;
	int i;

	i = 8;

	tmp = nbr;
	div_value = 1;
	base_len = ft_strlen(base);
	while (tmp)
	{
		tmp /= base_len;
		div_value *= base_len;
	}

	while(div_value >= 1)
	{
		file[i] = base[nbr / div_value];
		nbr %= div_value;
		div_value /= base_len;
		i++;
	}
}

/*Genrate a unique here_doc filename in the form ms_hd_xxxx *where xxx is the address of the content pointer*/
static char	*ft_generate_u_filename(char *content)
{
	char	*file;

	if (!content)
		return (NULL);
	file = malloc (30 * sizeof(char));
	if (!file)
		return (NULL);
	ft_memset(file, 0, 30 * sizeof(char));
	ft_strcpy(file, "/tmp/ms_");
	ft_putnbr_base_l((unsigned long) content, "0123456789abcdef", file);
	return (file);
}

/*Apply the here_doc redirection by creating a tmp file, copying the hd_buffer in it and redirect STDIN to it*/
int	ft_apply_r_heredoc(char *content)
{
	int	in_file;
	char	*file;

	file = NULL;

	file = ft_generate_u_filename(content);
	if (!file)
	{
		write(2,"File generation error!\n",24);
		return (1);
	}
	ft_dprintf(2,"file : %s\n", file); ////////////////////////////////////debug
	/// creer un fichier dans /temp -> dterminer le nom
	in_file = open(file, O_WRONLY | O_CREAT, 0666); // voir le cas d'etre sur que le fichier existe pas avant
	if (in_file == -1)
	{
		perror(file);
		return(1);
	}
	/// copier le contenu du buffer dans le fichier
	if (write(in_file, content, ft_strlen(content)) == -1)
	{
		perror(file);
		free(file);
		return(1);
	}
	//  fermer le fichier
	close(in_file);
// ouvrir le fichier
	in_file = open(file, O_RDONLY);
	if (in_file == -1)
	{
		perror(file);
		free(file);
		return(1);
	}
// faire un dup2 du fichier
	if (dup2(in_file, STDIN_FILENO) == -1)
	{
		perror(file);
		free(file);
		close(in_file);
		return(1);
	}
// faire un unlink()
	if (unlink(file) == -1)
	{
		perror(file);
		free(file);
		close(in_file);
		return(1);
	}
// fermer le fichier
	close(in_file);
	free(file);
	return (0);

}


void	ft_exec(t_node *node, int pipe_nb, t_shell *shell)
{
	char	**cmd_array;
	char	**env_array;
	char	*full_cmd;
	int		ret;
	struct stat file_stat;

	cmd_array = NULL;
	env_array = NULL;
	full_cmd = NULL;
	(void) pipe_nb;

	//[1]  si builtin => executer la builtin et quitter penser a la question du free quand side = center
	//[2]   si pipe_nb !=-1 -> gerer la redirection initiale

	//[3]  gerer les redirections heredocs etc... => soulever exception en cas d'erreur
	t_token *redir;

	redir = node->redir;
	int ret2;
	while(redir)
	{
		if (redir->type == R_OUT)
			ret2 = ft_apply_r_out(redir->content);
		else if (redir->type == R_IN)
			ret2 = ft_apply_r_in(redir->content);
		else if (redir->type == R_APPEND)
			ret2 = ft_apply_r_append(redir->content);
		else if (redir->type == R_HEREDOC)
			ret2 = ft_apply_r_heredoc(redir->content);

		if (ret2) /// On quitte en cas d'erreur
		{
			ft_free_shell(shell);
			exit (ret2);
		}

		redir = redir->next;
	}


/////[4] Si pas de token commande => free et  exit(0)

	if (node->cmd == NULL)
	{
		ft_free_shell(shell);
		exit (0);
	}
//////// [5] recuperation de lacommande / check si c'est un path ou un nom de commande a expanser
////////     verifications : le fichier existe / il est valide ( pas un repertoire) et il est executable
	if (ft_strchr(node->cmd->content, '/') != NULL)  // detection de '/'
	{

		full_cmd = ft_strdup(node->cmd->content);
		if (!full_cmd)
			exit (ft_malloc_error());
		if (access(full_cmd, F_OK) != 0 )
		{
			perror(full_cmd);
			free(full_cmd);
			ft_free_shell(shell);
			exit(127);
		}
	}
	else
	{
		ret = ft_get_full_cmd(&full_cmd ,node->cmd->content, shell);
		if (ret != 0)
		{
			ft_free_shell(shell);
			exit (ret);
		}
	}
	if (stat(full_cmd, &file_stat) == -1) {
		perror("stat");
		exit(1) ;
	}
	if (!S_ISREG(file_stat.st_mode) || !(file_stat.st_mode & S_IXUSR))
	{
		write(2, full_cmd, ft_strlen(full_cmd));
		if (S_ISDIR(file_stat.st_mode))
			write(2, ": Is a directory\n", 18);
		else
			write(2, ": Permission denied\n", 21);
		free(full_cmd);
		ft_free_shell(shell);
		exit (126);
    }


///////// [6] iitiaalisation des tableau de comande et env pour execve
	if (!ft_token_to_array(&node->cmd, &cmd_array))
		{
			write(2, "Error during malloc\n", 21);
			ft_free_shell(shell);
			exit(1);
		}
	if (!ft_push_env_vars(shell->env_vars, &env_array))
		{
			write(2, "Error during malloc\n", 21);
			ft_free_splitted(cmd_array);
			ft_free_shell(shell);
			exit(1);
		}
/////////[7] lancer execve => si echec ( free et exit code = 1 )
	if (execve(full_cmd, cmd_array , env_array) == -1)
	{
		write(2, "Error during execve\n", 21);
		free(full_cmd);
		ft_free_shell(shell);
		ft_free_splitted(env_array);
		ft_free_splitted(cmd_array);
		exit(1);
	}
}


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
	if (tree_root->type == N_PIPE) //pipe potentiellement plusieurs pipes a la suite
		exit_status = ft_exec_in_fork(tree_root, 0,  shell);
	}

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
