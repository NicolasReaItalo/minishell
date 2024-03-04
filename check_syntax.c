/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:21:18 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/04 17:37:18 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	syntax_error(t_token *stack, )
{
	char	*error;
		
	ft_printf("syntax error near unexpected token '%s'\n", error);
}

t_syntax_rule	*init_syntax_rules(void)
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
	t_syntax_rule *rules;

	ptr = ft_get_token(stack, -1);
	rules = init_syntax_rules();
	while (ptr)
	{
		while (rules[ptr->type] != -1 )	
		ptr = ptr->prev;
	}
}
