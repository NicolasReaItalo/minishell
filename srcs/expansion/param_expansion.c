/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:53:49 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/02 13:38:42 by nrea             ###   ########.fr       */
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

int	expanse_param(t_shell *shell, t_token *token, char **key, char *ifs, int *index, char *next, int in_quotes)
{
	int		i;
	char	*new;

	new = ft_get_var_value(*key, shell->env_vars, shell->shell_vars);
	i = 0;
	while (new[i] && !in_quotes && ft_strcmp(*key, "IFS") != 0)
	{
		if (ft_strchr(ifs, new[i]))
			new[i] = -1;
		i++;
	}
	*index = ft_strlen(token->content) + ft_strlen(new);
	if (new[0])
		token->content = ft_concat_3str(token->content, new, next);
	else
		case_empty_tab(token, next);
	if (!token->content)
		return (1);
	free (*key);
	*key = NULL;
	return (0);
}

int	expand_param(t_shell *shell, t_token *token)
{
	char	*key;
	int		in_quotes;
	char	*next;
	char	*ifs;
	int		index;

	in_quotes = 0;
	index = 0;
	if (!token->content)
		return (2);
	ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	if (!ifs)
		return (1);
	next = NULL;
	token->param_expanded = 1;
	key = find_next_param_expansion(token->content, &next, &in_quotes);
	while (key)
	{
		if (expanse_param(shell, token, &key, ifs, &index, next, in_quotes))
			return (1);
		if (ft_strlen(token->content))
			key = find_next_param_expansion(token->content + index, &next, &in_quotes);
	}
	if (ft_strchr(token->content, -1))
		if (field_splitting(token, token->content, next))
			return (1);
	return (0);
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
	in_quotes = 0;
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
