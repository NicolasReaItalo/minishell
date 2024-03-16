/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:21:18 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/16 15:46:40 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	syntax_error(char *error)
{
	ft_dprintf(2, "syntax error near unexpected token `%s'\n", error);
}
/*
t_syntax_rule	**init_syntax_rules(void)
{
	t_syntax_rule	*rules[10];
	int				i;
	int				j;
	int				next;
	int				prev;

	i = 0;
	while (i < 10)
	{
		rules[i]->token = i;
		if (i == AND || i == OR)
		{
			next = 456780;
			prev = 90;
		}
		else if (i == PIPE)
		{
			next = 45670;
			prev = 90;
		}
		else if (i >= 4 && i <= 7)
		{
			next = 0;
			prev = 82310;
		}
		else if (i == WORD)
		{
			next = 123456790;
			prev = 123456780;
		}
		else if (i == O_BRACKET)
		{
			next = 456780;
			prev = 0;
		}
		j = 0;
		if (!next)
			rules[i]->valid_next[j++] = WORD;
		else
		{
			while (next)
			{
				rules[i]->valid_next[j] = next % 10;
				next /= 10;
				j++;
			}
		}
		rules[i]->valid_next[j] = -1;
		j = 0;
		if (!prev)
			rules[i]->valid_prev[j++] = WORD;
		else
		{
			while (prev)
			{
				rules[i]->valid_prev[j] = prev % 10;
				prev /= 10;
				j++;
			}
		}
		rules[i]->valid_prev[j] = -1;
	}
	return rules;
}

int	check_syntax(t_token *stack)
{
	t_token	*ptr;
	t_syntax_rule **rules;
	int		i;

	ptr = ft_get_token(stack, -1);
	rules = init_syntax_rules();
	while (ptr)
	{
		i = 0;
		while ((rules[ptr->type])->valid_next[i] != -1 && i < 0)
		{
			if (ptr->next && ptr->next->type == (rules[ptr->type])->valid_prev[i])
				// ok
			i++;
		}
		ptr = ptr->prev;
	}
}*/

static char	*check_start_and_end(t_token *ptr)
{
	if (!ptr->next)
	{
		if ((ptr->type > 0 && ptr->type < 4) || ptr->type == 9)
			return (ptr->content);
		else
			return (NULL);
	}
	else if (!ptr->prev)
	{
		if ((ptr->type > 0 && ptr->type < 9))
			return (ptr->content);
		else
			return (NULL);
	}
	return (NULL);
}

static char	*check_syntax_node(t_token *ptr)
{
	int	prev_type;

	if (!ptr)
		return (NULL);
	if (ptr->type == -1)
		return (ptr->content);
	if (!ptr->next || !ptr->prev)
		return (check_start_and_end(ptr));
	prev_type = ptr->prev->type;
	if ((ptr->type == 2 || ptr->type == 3 || ptr->type == 8)
		&& ((prev_type > 0 && prev_type < 4) || prev_type == 9))
		return (ptr->prev->content);
	else if (ptr->type == 1
		&& !((prev_type > 3 && prev_type < 8) || prev_type == 0))
		return (ptr->prev->content);
	else if ((ptr->type >= 4 && ptr->type <= 7) && prev_type)
		return (ptr->prev->content);
	else if ((ptr->type == 0) && (prev_type == 8))
		return (ptr->prev->content);
	else if ((ptr->type == 9)
		&& !(prev_type == 2 || prev_type == 3 || prev_type == 9))
		return (ptr->prev->content);
	return (NULL);
}

int	check_syntax(t_token *stack)
{
	t_token	*ptr;
	char	*error;
	int		check_brackets;

	ptr = ft_get_token(stack, -1);
	check_brackets = 0;
	while (ptr)
	{
		error = check_syntax_node(ptr);
		if (ptr->type == 8)
			check_brackets++;
		else if (ptr->type == 9)
			check_brackets--;
		if (check_brackets < 0)
			error = ptr->content;
		if (error)
			return (syntax_error(error), 1);
		ptr = ptr->prev;
	}
	if (check_brackets)
		return (ft_dprintf(2, "syntax error : brackets unclosed\n"), 1);
	return (0);
}
