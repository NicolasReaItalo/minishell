/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:53:49 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/02 16:50:11 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

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

static void	case_empty_tab(t_token *token, char *next)
{
	char	*p;

	if (token->content[0] || next[0])
		p = ft_strjoin(token->content, next);
	else
		p = ft_strdup("");
	free(token->content);
	token->content = p;
}

int	expanse_param(t_shell *shell, t_token *token, char *next, t_expvar *vars)
{
	int		i;
	char	*new;

	new = ft_strdup(ft_get_var_value(vars->key, shell->env_vars, shell->shell_vars));
	if (!new)
		return (1);
	i = 0;
	while (new[i] && !vars->in_quotes && ft_strcmp(vars->key, "IFS") != 0)
	{
		if (ft_strchr(vars->ifs, new[i]))
			new[i] = -1;
		i++;
	}
	vars->index = ft_strlen(token->content) + ft_strlen(new);
	if (new[0])
		token->content = ft_concat_3str(token->content, new, next);
	else
		case_empty_tab(token, next);
	if (!token->content)
		return (free(new), 1);
	free (vars->key);
	vars->key = NULL;
	return (free(new), 0);
}

int	expand_param(t_shell *shell, t_token *token)
{
	char		*next;
	t_expvar	*vars;

	vars = malloc(sizeof(t_expvar));
	if (!vars)
		return (1);
	vars->in_quotes = 0;
	vars->index = 0;
	if (!token->content)
		return (2);
	vars->ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	if (!(vars->ifs))
		return (1);
	next = NULL;
	token->param_expanded = 1;
	vars->key = find_next_param_expansion(token->content, &next
		, &(vars->in_quotes));
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

char	*expand_param_redir(char *str, t_shell *shell)
{
	char	*new;
	char	*next;
	char	*output;
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
		new = ft_get_var_value(vars->key, shell->env_vars, shell->shell_vars);
		free (vars->key);
		output = ft_concat_3str(output, new, next);
		if (!output)
			return (free(vars), NULL);
		vars->key = find_next_param_expansion(output, &next, &(vars->in_quotes));
	}
	return (free(vars), output);
}
