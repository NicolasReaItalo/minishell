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
// #include "env_variables.h"

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
/* 
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
*/
/*
// cree une serie de token pour le field_splitting
t_token	*tab_to_list(char **words)
{
	t_token *new;
	t_token *token;
	t_token	*ptr;

	token = NULL;
	while (*words)
	{
		new = new_token(*words, ft_strlen(*words) + 1);
		if (!new)
			return (NULL);
		new->next = NULL;
		new->prev = NULL;
		new->type = WORD;
		if (!token)
			token = new;
		else
		{
			ptr = ft_get_token(token, -1);
			new->prev = ptr;
			ptr->next = new; // FIXME: Il n' a pas de conversion en token	
		}	
		words++; 
	}
	return (token);
}*/