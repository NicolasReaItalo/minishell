/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:53:49 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/29 15:56:21 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

static int	is_valid_param_char(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

// Fonction qui prend en entree une chaine de caractere et renvoie 
// une chaine ayant les criteres d'une key
static char	*find_next_param_expansion(char *str, char **next, int *in_quotes)
{
	int		len;

	len = 0; 
	*in_quotes = 0;
	while (*str)
	{
		if (*str == '\"')
		{
			if (!*in_quotes)
				*in_quotes = 1;
			else 
				*in_quotes = 0;
			str++;
			continue ;
		}
		if (!*in_quotes && *str == '\'')
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

//Concatene 3 chaines de caracteres
// first alloue, second, third non alloue   
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
		return (NULL);
	if (!output)
		return (free(first_concat), NULL);
	return (free(first_concat), output);
}

//Fonction qui gere l'expansion des parametres ($VAR) 
//return une chaine de caractere allouee
// char	*expand_param(char *str, t_shell *shell, t_token *token)
// {
// 	char	*key;
// 	char	*new;
// 	char	*next;
// 	char	*output;
// 	int		in_quotes;

// 	if (!str)
// 		return (NULL);
// 	next = NULL;
// 	output = ft_strdup(str);
// 	if (!output)
// 		return (NULL);
// 	free (str);  // <---------------------
// 	key = find_next_param_expansion(output, &next, &in_quotes);
// 	if (!key)
// 		return (output);
// 	while (key)
// 	{
// 		new = ft_get_var_value(key, shell->env_vars, shell->shell_vars);

// 		if (contains_ifs(token, shell, new) && !in_quotes)
// 		{
// 			if (field_splitting(token, shell, new, output, next))
// 				return (NULL);
// 			printf("[DEBUG]token.content[%s]\n", token->content);
// 			printf("[DEBUG]output[%s]\n", output);
// 		}
// 		else
// 		{
// 			output = ft_concat_3str(output, new, next); //C'est sur new que je dois appliquer l'IFS
// 			if (!output)
// 				return (NULL);
// 		}
// 		free(key);
// 		key = find_next_param_expansion(output, &next, &in_quotes);
// 	}
// 	return(output);
// }


//Fonction qui gere l'expansion des parametres ($VAR) 
//return une chaine de caractere allouee
char	*expand_param(t_shell *shell, t_token *token)
{
	char	*key;
	char	*new;
	char	*next;
	int		in_quotes;
	char 	*expanded;
	printf("[DEBUG] on commence l'expansion[%s]\n", token->content);
	if (!token->content)
		return (NULL);
	next = NULL;
	token->param_expanded = 1;
	// output = ft_strdup(token->content);
	// if (!output)
	// 	return (NULL);
	// free (token->content);  // <---------------------
	key = find_next_param_expansion(token->content, &next, &in_quotes);
	if (!key)
	{
		// token->content = output;
		return NULL;
	}
	while (key)
	{
		new = ft_get_var_value(key, shell->env_vars, shell->shell_vars);

		if (contains_ifs(token, shell, new) && !in_quotes)
		{
			if (field_splitting(token, shell, new, token->content, next))
				return (NULL);
		}
		else
		{
			expanded = ft_concat_3str(token->content, new, next); //C'est sur new que je dois appliquer l'IFS
			if (!expanded)
				return (NULL);
			token->content = expanded;
		}
		free(key);
		key = find_next_param_expansion(token->content, &next, &in_quotes);
	}
	return(NULL);
}






char	*expand_param_redir(char *str, t_shell *shell)
{
	char	*key;
	char	*new;
	char	*next;
	char	*output;
	int		in_quotes;

	if (!str)
		return (NULL);
	next = NULL;
	output = ft_strdup(str);
	if (!output)
		return (NULL);
	key = find_next_param_expansion(output, &next, &in_quotes);
	if (!key)
		return (output);
	while (key)
	{
		new = ft_get_var_value(key, shell->env_vars, shell->shell_vars);
		free (key);
		output = ft_concat_3str(output, new, next);
		if (!output)
			return (NULL);
		key = find_next_param_expansion(output, &next, &in_quotes);
	}
	return (output);
}
