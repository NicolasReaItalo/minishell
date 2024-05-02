/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyeux <joyeux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:12:10 by joyeux            #+#    #+#             */
/*   Updated: 2024/05/02 23:18:36 by joyeux           ###   ########.fr       */
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

	new = ft_strdup(ft_get_var_value(vars->key, shell->env_vars,
				shell->shell_vars));
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

int	expanse_param_redir(t_expvar *vars, t_shell *shell, char **output,
		char **next)
{
	vars->new = ft_get_var_value(vars->key, shell->env_vars, shell->shell_vars);
	free (vars->key);
	*output = ft_concat_3str(*output, vars->new, *next);
	if (!*output)
		return (free(vars), 1);
	vars->key = find_next_param_expansion(*output, next,
			&(vars->in_quotes));
	return (0);
}
