/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:53:49 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/21 15:09:15y tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"
#include "env_variables.h"

//word_expansion recoit en argument le node EXEC ainsi que les variables d'environnement.
//Il modifie le node pour expandre les variables
// 1. Parcourir redir et cmd pour voir s'il y a un $
// 2. Parcourir les caracteres qui suivent jusqu'a non conformite(voir ft_is_valid_key) et extraire la chaine de caracteres
// 3. Verifier si cette chaine de caractere fait partie des variables d'environnement
// 3. Remplacer la chaine de caractere
// !!!L'expansion ne doit pas se faire entre ' '
// ??? Expansion $?

static int	is_valid_param_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

// Fonction qui prend en entree une chaine de caractere et renvoie 
// une chaine ayant les criteres d'une key
char	*find_next_param_expansion(char *str, char **next)
{
	int		len;

	len = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
		}
		else if (*str == '$' && *(str + 1) == '?')
			return (*str = '\0', *next = str + 2, ft_substr(str + 1, 0, 1));
		else if (*str == '$' && is_valid_param_char(*(str + 1)))
		{
			*str = '\0';
			str++;
			while (is_valid_param_char(*(str + len)))
				len++;
			*next = str + len;
			return (ft_substr(str, 0, len));
		}						
		str++;
	}
	return (NULL);
}

static char	*ft_concat_3str(char *first, char *second, char *third)
{
	char	*output;
	char	*first_concat;

	first_concat = ft_strjoin(first, second);
	if (!first_concat)
		return (free(first), NULL);
	output = ft_strjoin(first_concat, third);
	free (first);
	if (!output)
		return (free(first_concat), NULL);
	return (free(first_concat), output);
}

//Fonction qui remplace une chaine de caractere en gerant l'expansion des variables
//return une chaine de caractere allouee
char	*expand_param(char *str, t_shell *shell)
{
	char	*key;
	char	*new;
	char	*next;
	char	*output;

	if (!str)
		return (NULL);
	next = NULL;
	output = ft_strdup(str);
	if (!output)
		return (NULL);
	free (str);
	key = find_next_param_expansion(output, &next);
	if (!key)
		return (output);
	while (key)
	{
		new = ft_get_var_value(key, shell->env_vars, shell->shell_vars);
		free (key);
		output = ft_concat_3str(output, new, next);
		key = find_next_param_expansion(output, &next);
	}
	return (output);
}

// Gestion de l'IFS apres l'expansion des parametres
int	field_splitting(t_token *token, t_shell *shell)
{
	char	*ifs;
	//char	*next;
	char	*str;
	t_token	*new;

	ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	str = token->content;
	while (*str)
	{
		// Attention apres expansion il peux y avoir plusieurs caracteres ifs d'affilee (et au debut et a la fin)
		// Peux etre essayer de representer sur un schema drawio 
		if (ft_strchr(ifs, *str) && !ft_strchr(ifs, *(str + 1)))
		{
			new = new_token(str + 1, ft_strlen(str + 1) + 1);
			if (!new)
				return (1);
			new->type = token->type;
			new->next = token->next;
			token->next = new;
			new->prev = token;
			if (new->next)
				new->next->prev = new;
			*str = '\0';
			return (0);
		}
		str++;
	}
	return (0);
}

// Cette fonction gere le cycle d'expansions pour le node de type exec fournit en argument
// pour chaques token :  parameter_expansion -> IFS -> pathname_expansion -> quote removal
// !!! pour redir verif les operations a faire
int	word_expand(t_node *node, t_shell *shell)
{
	t_token	*token;
	int		error;

	if (!node)
		return (4);
	token = node->cmd;
	while (token)
	{
		token->content = expand_param(token->content, shell);
		if (!token->content)
			return (1);
		error = field_splitting(token, shell);
		if (error)
			return (error);
		token = token->next;	
	}
	token = node->redir;
	while (token)	
	{
		token->content = expand_param(token->content, shell);
//		TODO: que faire si return NULL?
		if (!token->content)
			return (1);
		token = token->next;	
	}
	return (0);
}
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
//gcc -g3 srcs/execution/param_expansion.c srcs/env_variables/*.c -I./include/ -I./libft/ -L./libft/ -lft -o param_expansion 

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

char	*ft_handle_token_errors(int error)
{
	if (error == 1)
		return ("Bad alocation");
	if (error == 2)
		return ("unclosed quotes");
	if (error == 3)
		return ("Empty string");
	if (error == 4)
		return ("Empty node");
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
	ft_init_env_vars(shell.env_vars, &shell.shell_vars);
	ft_fetch_env_vars(shell.env_vars, envp);
//  ft_dprintf(1, "carac IFS : \"%s\"\n", ft_get_var_value("IFS", shell.env_vars, shell.shell_vars));
	token_error = tokenise(argv[1], &stack);
	if (token_error)
	{
		ft_dprintf(2, "tokenisation error: %s\n", ft_handle_token_errors(token_error));
		kill_stack(&stack);
		return (1);
	}
	syntax_error = check_syntax(stack);
	if (syntax_error)
	{
		kill_stack(&stack);
		return (2);
	}
	ft_redirections(&stack);
	tree = ft_create_tree(&stack, &tree_error, 2);
	if (tree_error)
	{
		ft_handle_tree_error(tree_error);
		ft_free_tree(tree);
		return (3);
	}
	ft_dprintf(1, "--------------------\n");
	show_tree(tree, 0);
	ft_dprintf(1, "----------After----------\n");
	expand_error = word_expand(tree, &shell);
	if (expand_error)
	{
		ft_dprintf(2, "expansion error: %s\n", ft_handle_token_errors(expand_error));
		ft_free_tree(tree);
		ft_free_env_vars(shell.env_vars, &shell.shell_vars);
		return (4);
	}
	show_tree(tree, 0);
	ft_free_tree(tree);
	ft_free_env_vars(shell.env_vars, &shell.shell_vars);
	return (0);
}


//gcc -g3 srcs/execution/param_expansion.c srcs/env_variables/*.c srcs/parsing/*.c test/utils/*.c -I./include/ -I./libft/ -I./test -L./libft/ -lft -lreadline -o param_expansion 

//valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=valgrind.txt  ./param_expansion '<$SHLVL <<eof echo$SHELL $?-l la$? >file'
