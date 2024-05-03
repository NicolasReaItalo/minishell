/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:53:49 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/03 16:08:19 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

static int	init_vars_p(t_expvar **vars, t_token *token, t_shell *shell)
{
	*vars = malloc(sizeof(t_expvar));
	if (!*vars)
		return (1);
	(*vars)->in_quotes = 0;
	(*vars)->index = 0;
	if (!token->content)
		return (free(*vars), 2);
	(*vars)->ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	if (!(*vars)->ifs)
		return (free(*vars), 1);
	return (0);
}

int	expand_param(t_shell *shell, t_token *token)
{
	char		*next;
	t_expvar	*vars;
	int			error;

	error = init_vars_p(&vars, token, shell);
	if (error)
		return (error);
	next = NULL;
	token->param_expanded = 1;
	vars->key = find_next_param_expansion(token->content, &next,
			&(vars->in_quotes));
	while (vars->key)
	{
		if (expanse_param(shell, token, next, vars))
			return (1);
		if (ft_strlen(token->content))
			vars->key = find_next_param_expansion(token->content
					+ vars->index, &next, &(vars->in_quotes));
	}
	if (ft_strchr(token->content, -1))
		if (field_splitting(token, token->content, next))
			return (1);
	return (0);
}

static char	*quotes_gestion(char *str, int *in_quotes)
{
	while (*str == '\"')
	{
		if (!*in_quotes)
			*in_quotes = 1;
		else
			*in_quotes = 0;
		str++;
	}
	if (!*in_quotes && *str == '\'')
	{
		str++;
		while (*str && *str != '\'')
			str++;
	}
	return (str);
}

// Fonction qui prend en entree une chaine de caractere et renvoie
// une chaine ayant les criteres d'une key
char	*find_next_param_expansion(char *str, char **next, int *in_quotes)
{
	int		len;
	char	*ret;

	len = 0;
	while (*str)
	{
		str = quotes_gestion(str, in_quotes);
		if (*str == '$')
		{
			ret = dollar_sign(&str, next, &len);
			if (ret)
				return (ret);
		}
		str++;
	}
	return (NULL);
}

char	*expand_param_redir(char *str, t_shell *shell)
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
	vars->key = find_next_param_expansion(output, &next, &(vars->in_quotes));
	if (!(vars->key))
		return (output);
	while (vars->key)
	{
		if (expanse_param_redir(vars, shell, &output, &next))
			return (NULL);
	}
	return (free(vars), output);
}
