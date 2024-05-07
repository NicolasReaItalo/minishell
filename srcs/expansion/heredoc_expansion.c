/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:39:51 by nrea              #+#    #+#             */
/*   Updated: 2024/05/07 16:42:20 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

//Concatene 3 chaines de caracteres
// first alloue, second alloue, third non alloue
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

char	*dollar_sign_heredoc(char **str, char **next, int *len)
{
	if (**str == '$' && *(*str + 1) == '?')
		return (**str = '\0', *next = *str + 2, ft_substr(*str + 1, 0, 1));
	else if (**str == '$' && (is_valid_first_param_char(*(*str + 1))))
	{
		**str = '\0';
		(*str)++;
		while (*(*str + *len) && is_valid_param_char(*(*str + *len)))
			(*len)++;
		*next = *str + *len;
		return (ft_substr(*str, 0, *len));
	}
	else if (**str == '$' && unimplemented_special_var(*(*str + 1)))
	{
		**str = '\0';
		(*str)++;
		*next = *str + 1;
		return (ft_substr(*str, 0, 1));
	}
	return (NULL);
}

// Fonction qui prend en entree une chaine de caractere et renvoie
// une chaine ayant les criteres d'une key
char	*find_next_param_expansion_heredoc(char *str, char **next)
{
	int		len;
	char	*ret;

	len = 0;
	while (*str)
	{
		if (*str == '$')
		{
			ret = dollar_sign_heredoc(&str, next, &len);
			if (ret)
				return (ret);
		}
		if (*str)
			str++;
	}
	return (NULL);
}

int	expanse_param_redir_heredoc(t_expvar *vars, t_shell *shell, char **output,
		char **next)
{
	vars->new = ft_strdup(ft_get_var_value(vars->key, shell->env_vars,
				shell->shell_vars));
	if (!vars->new)
		return (1);
	free (vars->key);
	*output = ft_concat_3str(*output, vars->new, *next);
	if (!*output)
		return (free(vars->new), free(vars), 1);
	vars->key = find_next_param_expansion_heredoc(*output, next);
	return (free(vars ->new), 0);
}

char	*expand_param_redir_heredoc(char *str, t_shell *shell)
{
	char		*next;
	char		*output;
	t_expvar	*vars;

	if (!str)
		return (NULL);
	vars = malloc(sizeof(t_expvar));
	if (!vars)
		return (NULL);
	vars->in_quotes = 0;
	next = NULL;
	output = ft_strdup(str);
	if (!output)
		return (free(vars), NULL);
	vars->key = find_next_param_expansion_heredoc(output, &next);
	if (!(vars->key))
		return (free(vars), output);
	while (vars->key)
	{
		if (expanse_param_redir_heredoc(vars, shell, &output, &next))
			return (free(vars), NULL);
	}
	return (free(vars), output);
}
