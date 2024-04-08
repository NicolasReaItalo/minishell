/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:53:49 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/08 17:51:25 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

static int	is_valid_param_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

// Fonction qui prend en entree une chaine de caractere et renvoie 
// une chaine ayant les criteres d'une key
static char	*find_next_param_expansion(char *str, char **next)
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

//Fonction qui gere l'expansion des parametres ($VAR) 
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

char	*expand_param_redir(char *str, t_shell *shell)
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
