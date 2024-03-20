/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:53:49 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/20 17:16:22 by tjoyeux          ###   ########.fr       */
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


/*Checks if the key  string is a valid key for an environement
variable
returns 1 in case o success, 0 otherwise
RULES
no empty string
char : a-z or A-Z or 1-9 or _
first char must not be a  digit*/
//TODO: Voir si j'ai vraiement besoin de cette fonction
int	ft_is_valid_key_char(char *key)
{
	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (*key)
	{
		if (!ft_isalpha(*key) && !ft_isdigit(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

static int	is_valid_param_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

// Fonction qui prend en entree une chaine de caractere et renvoie une chaine ayant les criteres d'une key
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
		{
//			param = ft_substr(str, 1, 1);
			*str = '\0';
			*next = str + 2;
//			return (param);
			return (ft_substr(str + 1, 0, 1));
		}
		else if (*str == '$' && is_valid_param_char(*(str + 1)))
		{
			*str = '\0';
			str++;
			while (is_valid_param_char(*(str + len)))
			{
				len++;
			}
			*next = str + len;
			return(ft_substr(str, 0, len));		
		}						
		str++;
	}
	return (NULL); 
}

static char	*ft_concat_3str(char *first, char *second, char *third)
{
	char	*output;
	char	*first_concat;

//	if (!first || !second || !third)
//		return (NULL);
	first_concat = ft_strjoin(first, second);
	free (first);
	output = ft_strjoin(first_concat, third);
	return (free(first_concat), output);	
}

//Fonction qui remplace une chaine de caractere en gerant l'expansion des variables
//return une chaine de caractere allouee
char	*expand_param(char *str, t_shell *shell)
{
	char	*key;
	char	*new;
	char	*next;
	char	*out1;
	char	*output;
	
	if (!str)
		return (NULL);
	next = NULL;
	output = ft_strdup(str);
	key = find_next_param_expansion(output, &next);
	if (!key)
		return (output);
	while (key)
	{
		new = ft_get_var_value(key, shell->env_vars, shell->shell_vars);
		free (key);
		//On doit joindre les trois bouts
		output = ft_concat_3str(output, new, next);
//		free(out1);
		key = find_next_param_expansion(output, &next);
//		if (!key)
//			break;	
	}
	return (output);	
}

// Cette fonction gere le cycle d'expansions pour le node de type exec fournit en argument
// pour chaques token :  parameter_expansion -> IFS -> pathname_expansion -> quote removal
// !!! pour redir verif les operations a faire
void	word_expand(t_node node, t_shell shell)
{
		
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
//	char	*next;
	t_shell	shell;	

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
}
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

//gcc -g3 srcs/execution/param_expansion.c srcs/env_variables/*.c -I./include/ -I./libft/ -L./libft/ -lft -o param_expansion 