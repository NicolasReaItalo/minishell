/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:23:26 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/02/29 14:39:08 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

// Check if it's a whitespace
int	is_wspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&'
		|| c == '(' || c == ')');
}
/*
int	error_msg(int i)
{
	return (i);		
}*/

void	kill_stack(t_token **stack)
{
	t_token	*tmp;

	while (*stack)
	{
		free((*stack)->content);
		tmp = *stack;
		*stack = (*stack)->next;
		free(tmp);
	}
}

t_token	*new_token(char *str, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_substr(str, 0, len);
	if (!(new->content))
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

// Pass whitespace
// Identifie type du token
// Pass whitespace
// Return new pointer in string
char	*next_token(char *str, t_token **new, int *error_code)
{
	int	i;

	i = 0;
	while (*str && is_wspace(*str))
		str++;
	if (!*str)
		return (*error_code = 2, NULL);
	else if (*str == 34 || *str == 39)
	{
		while (*(str + ++i) && *(str + i) != *str)
		{
		}
		if (!*(str + i))
			return (*error_code = 2, NULL);
		i++;
		*new = new_token(str, i);
		if (!*new)
			return (*error_code = 1, NULL);
		str += i;
	}
	else if (is_operator(*str))
	{
		if (ft_strchr("|<>&", *str) && (*str == *(str + 1)))
			*new = new_token(str++, 2);
		else
			*new = new_token(str, 1);
		if (!*new)
			return (*error_code = 1, NULL);
		str++;
	}	
	else
	{
		while (*(str + i) && !is_wspace(*(str + i)) && !is_operator(*(str + i)))
			i++;
		*new = new_token(str, i);
		if (!*new)
			return (*error_code = 1, NULL);
		str += i;
	}
	while (*str && is_wspace(*str))
		str++;
	return (str);
}
/*
t_token	*add_token(t_token *stack, t_token *new)
{
	if (!stack)
		stack = new;
	else 
	{
		new->next = stack;
		stack = new;
	}
	return (stack);
}
*/

t_token	*add_token(t_token *stack, t_token *new)
{
	if (!stack)
		return (new);
	else if (!new)
		return (stack);
	else
	{
		new->next = stack;
		stack = new;
	}
	return (stack);
}

void	put_type_in_stack(t_token *stack, int *error_code)
{
	int	check_brackets;

	check_brackets = 0;
	while (stack)
	{
		if (stack->content[0] == '|')
		{
			if (stack->content[1] == '|')
				stack->type = OR;
			else
				stack->type = PIPE;
		}
		else if (stack->content[0] == '<')
		{
			if (stack->content[1] == '<')
				stack->type = R_HEREDOC;
			else
				stack->type = R_IN;
		}
		else if (stack->content[0] == '>')
		{
			if (stack->content[1] == '>')
				stack->type = R_APPEND;
			else
				stack->type = R_OUT;
		}
		else if (stack->content[0] == '&')
		{
			if (stack->content[1] == '&')
				stack->type = AND;
			else
			{
				stack->type = WORD;
				*error_code = 3;
			}
		}
		else if (stack->content[0] == '(')
		{
			stack->type = O_BRACKET;
			check_brackets--;
		}
		else if (stack->content[0] == ')')
		{
			stack->type = C_BRACKET;
			check_brackets++;
		}
		else
			stack->type = WORD;
		if (check_brackets < 0)
			*error_code = 4;
		stack = stack->next;
	}
	if (check_brackets)
		*error_code = 4;
}

// Parse the prompt and create a stack (last element is first in stack)
// Error codes: 0 : OK
//				1 : bad allocation
//				2 : ' or " not closed
//				3 : & alone
//				4 : problem with brackets ()
int	tokenise(char *str, t_token **stack)
{
	t_token	*new;
	int		error_code;

	new = NULL;
	error_code = 0;
	while (*str)
	{
		new = NULL;
		str = next_token(str, &new, &error_code);
		if (!str)
			return (kill_stack(stack), error_code);
		if (new)
			*stack = add_token(*stack, new);
	}
	put_type_in_stack(*stack, &error_code);
	if (error_code)
		kill_stack(stack);
	return (error_code);
}
/*
t_token	*tokenise(char *str)
{
	char	*p;
	int		i;
	char	*s;
	t_token	*stack;
	
	
	while(is_wspace(*str))
		str++;
	p = str;
		i = 0;
	stack = NULL;
	while (*(p + i) && !is_operator(*(p + i))&& !is_wspace(*(p+ i))) 
		i++;
	s = NULL;
	s = ft_substr(str, 0, i);
	if (!s)
		return (NULL);
	stack = ft_add_node(stack, );
	if (!stack)
	{
		free(s);
		return (NULL);
	}
}*/

/*
#include <stdio.h>
int	main(int argc,char **argv)
{
	int	i;
	t_token *stack;
	t_token *stack_copy;
	int error;
//	char arg[] = "ec\"h'o\"'";
	
	if (argc != 2)
		return (1);
	stack = NULL;
	error = tokenise(argv[1], &stack);
	if (error)
		return (printf("ERROR : %d\n", error));
	stack_copy = stack;
	i = 0;
	while (stack)
	{
		printf("TOKEN %d : \e[31m%s\e[0m%%\ttype : %d\n", i, i
			stack->content, stack->type);
		i++;
		stack = stack->next;
	}
	kill_stack(&stack_copy);
	return (error);
}
*/