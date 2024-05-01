/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:56:44 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/01 13:36:26 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

// Check if there is only '*' in a string
int	only_stars(char *pattern)
{
	while (*pattern)
	{
		if (*pattern != '*')
			return (0);
		pattern++;
	}
	return (1);
}

int	contains_ifs(t_token *token, t_shell *shell, char *str)
{
	char	*ifs;
//	char	*str;

	(void)token;
	ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	if (!ifs)
		return (0);
//	str = token->content;
	while (*str)
	{
		if (ft_strchr(ifs, *str))
			return (1);
		str++;
	}
	return (0);
}

// Si le nb tokens est superieur a 2 avancer le pointeurs en fonction
/*t_token	*advance_token(t_token *token, int *nb_token)
{
	token = token->next;
	*nb_token -= 2;
	while (*nb_token > 0)
	{
		token = token->next;
		(*nb_token)--;
	}
	*nb_token = 1;
	return (token);
}*/

t_token	*advance_token(t_token *token, int type)
{
	if (type == 1)
	{
		while (token && token->param_expanded)
			token = token->next;
	}
	else if (type == 2)
	{
		while (token && token->path_expanded)
			token = token->next;
	}
	return (token);
}

int	is_only_whitespaces(char *str)
{
	while (*str)
	{
		if (!is_wspace(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	expand_param_cmd(t_token *token, t_shell *shell)
{
	expand_param(shell, token);
	if (is_only_whitespaces(token->content))
		return (2);
	return (0);
}

static int	expand_pathname_(t_token *token)
{
	token->path_expanded = 1;
	if (ft_strchr(token->content, '*') && !pathname_in_quotes(token->content))
	{
		if (expand_pathname_cmd(token))
			return (1);
	}
	else
	{
		unquote_content(token->content);
	}
//	token = advance_token(token, nb_token);

	return (0);

}
// Cycle d'expansions pour le node de type exec fournit en argument
// pour chaques token :
//   parameter_expansion -> IFS -> pathname_expansion -> quote removal
// TODO: !!! pour redir verif les operations a faire
int	word_expand(t_node *node, t_shell *shell)
{
	t_token	*token;
//	int		nb_token;
	int		error;
	t_token	*to_delete;

	if (!node)
		return (4);
	// Faire l'expansion des params ($VAR) et l'IFS de cmd
	token = node->cmd;
	while (token)
	{
		error = expand_param_cmd(token, shell);
		if (error == 2)//Si il ný a que des whitespaces
		{
			//supprimer le token
			if (token->prev)
			{
				token->prev->next =token->next;
			}
			else
				node->cmd = token->next;
			if (token->next)
				token->next->prev = token->prev;
			to_delete = token;
			token = token->next;
			ft_free_token(&to_delete);
		}
//		if (expand_cmd(token, shell, &nb_token))
		else if (error == 1)
			return (1);
		else
			token = advance_token(token, 1);
	}
	// Faire l'expansion du pathname (*) et l'unquotting
	token = node->cmd;
	while (token)
	{
		error = expand_pathname_(token);
		if (error)
			return (1);
		token = advance_token(token, 2);
	}
	// printf("[DEBUG] node->cmdcontent = [%s]\n", node->cmd->content);
	// Faire l'expansion des redirections
	token = node->redir;
	while (token)
	{
		if ((token->type == R_IN || token->type == R_OUT || token->type == R_APPEND)
			&& expand_redir(token, shell))
			return (1);
		token = token->next;
	}
	return (0);
}
// SERIE DE MAINS
/*
int	main(int argc, char **argv, char **envp)
{
	char	*str;
//	char	*next;
	t_shell	shell;

	if (argc < 2)
		return (0);
	ft_init_env_vars(shell.env_vars, &shell.shell_vars);
	ft_fetch_env_vars(shell.env_vars, envp);
//	next = NULL;
//	str = find_next_param_expansion(argv[1], &next);
	str = expand_param(argv[1], &shell);
//	ft_dprintf(1, "Key : %s\nAfter : %s\nNext Word : %s\n", str, argv[1], next);
	ft_dprintf(1, "Before : %s\nAfter : %s\n\n", argv[1], str);
	free (str);
	ft_free_env_vars(shell.env_vars, &shell.shell_vars);
	return (0);
}*/
//gcc -g3 srcs/execution/param_expansion.c srcs/env_variables/*.c
//     -I./include/ -I./libft/ -L./libft/ -lft -o param_expansion

/*
// main de test du strjoin special
int	main(int argc, char **argv)
{
	char *first = ft_strdup(argv[1]);
	char *third = ft_strdup(argv[3]);
	char *output = ft_concat_3str(first, argv[2], third);
	ft_dprintf(1, "%s\n", output);
	free (first);
	free (third);
	free (output);
	return (0);
}*/

/*
char	*ft_handle_token_errors(int error)
{
	if (error == 1)
		return ("Bad allocation");
	if (error == 2)
		return ("unclosed quotes");
	if (error == 3)
		return ("Empty string");
	if (error == 4)
		return ("Empty node");
	if (error == 5)
		return ("ambiguous redirect");
	if (error == 6)
		return ("unable to open directory");
	return ("");
}
#include "minishell.h"
#include "tests.h"
#include "token.h"
int	main(int argc, char **argv, char **envp)
{
	t_token	*stack;
	t_node	*tree;
	int		token_error;
	int		syntax_error;
	int		tree_error;
	int		expand_error;
	t_shell	shell;

	if (argc != 2)
		return (1);
	token_error = 0;
	syntax_error = 0;
	tree_error = 0;
	expand_error = 0;
	tree = NULL;
	stack = NULL;
	if (!ft_init_env_vars(shell.env_vars, &shell.shell_vars))
		return (1);
	ft_fetch_env_vars(shell.env_vars, envp);
	token_error = tokenise(argv[1], &stack);
	if (token_error)
	{
		ft_dprintf(2, "tokenisation error: %s\n",
		ft_handle_token_errors(token_error));
		kill_stack(&stack);
		return (1);
	}
	syntax_error = check_syntax(stack);
	if (syntax_error)
	{
		kill_stack(&stack);
		ft_free_env_vars(shell.env_vars, &shell.shell_vars);
		return (2);
	}
	ft_redirections(&stack, &shell);
	tree = ft_create_tree(&stack, &tree_error, 2);
	if (tree_error)
	{
		ft_handle_tree_error(tree_error);
		ft_free_tree(&tree);
		return (3);
	}
	ft_dprintf(1, "--------------------\n");
	show_tree(tree, 0);
	ft_dprintf(1, "----------After----------\n");
	expand_error = word_expand(tree, &shell);
	if (expand_error)
	{
	//	ft_dprintf(2, "expansion error: %s\n",
	//		ft_handle_token_errors(expand_error));
		ft_free_tree(&tree);
		ft_free_env_vars(shell.env_vars, &shell.shell_vars);
		return (4);
	}
	show_tree(tree, 0);
	ft_free_tree(&tree);
	ft_free_env_vars(shell.env_vars, &shell.shell_vars);
	return (0);
}*/


//gcc -g3 srcs/expansion/*.c srcs/env_variables/*.c srcs/parsing/*.c test/utils/*.c -I./include/ -I./libft/ -I./test -L./libft/ -lft -lreadline -o param_expansion

//valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes
//   --trace-children=yes --suppressions=valgrind.txt
//   ./param_expansion '<$SHLVL <<eof echo$SHELL $?-l la$? >file'

// gcc -g3 srcs/*.c srcs/execution/*.c srcs/builtins/*.c srcs/expansion/*.c srcs/env_variables/*.c srcs/parsing/*.c test/utils/*.c -I./include/ -I./libft/ -I./test -L./libft/ -lft -lreadline -o param_expansion
