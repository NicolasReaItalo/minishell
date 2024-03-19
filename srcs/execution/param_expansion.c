/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:53:49 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/19 18:43:39 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

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

// Fonction qui prend en entree une chaine de caractere et renvoie une chaine ayant les criteres d'une key
char	*find_next_param_expansion(char *str)
{
	char	*param;
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
		else if (*str == '$')
		{
			str++;
			while (ft_isalpha(*(str + len)) || ft_isdigit(*(str + len)) || *(str + len) == '_')
			{
				len++;
			}
			return(ft_substr(str, 0, len));		
		}						
		str++;
	}
	return (NULL); 
}

// Fonction prend une chaine de caractere et gere l'expansion de toutes les variables
// return une chaine de caractere 
char	*expand_param(char *str, t_shell *shell)
{
	char	*key;
	char	*new;

	while (1)
	{
		key = find_next_param_expansion(str);
		if (!key)
			break;
		new = ft_get_var_value(key, shell->env_vars, shell->shell_vars);
		
	}
	
}

// Cette fonction gere le cycle d'expansions pour le node de type exec fournit en argument
// pour chaques token :  parameter_expansion -> IFS -> pathname_expansion -> quote removal
// !!! pour redir verif les operations a faire
void	word_expand(t_node node, t_shell shell)
{
		
}

int	main(int argc, char **argv)
{
	char	*str;
	
	str = find_next_param_expansion(argv[1]);
	ft_dprintf(1, "%s\n", str);
	free (str);
	return (0);
}

// gcc srcs/execution/param_expansion.c -I./include/ -I./libft/ -L./libft/ -lft -o param_expansion