/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:41:59 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/07 12:24:38 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

// char	*next_token_operators(char **str, t_token **new, int *error_code)
// {
// 	int	i;

// 	i = 0;
// 	if (**str == 34 || **str == 39)
// 	{
// 		while (*(*str + ++i) && *(*str + i) != **str)
// 			;
// 		if (!*(*str + i))
// 			return (*error_code = 2, NULL);
// 		*new = new_token(*str, ++i);
// 		if (!*new)
// 			return (*error_code = 1, NULL);
// 		*str += i;
// 	}
// 	else if (is_operator(**str))
// 	{
// 		if (ft_strchr("|<>&", **str) && (**str == *(*str + 1)))
// 			*new = new_token((*str)++, 2);
// 		else
// 			*new = new_token(*str, 1);
// 		if (!*new)
// 			return (*error_code = 1, NULL);
// 		(*str)++;
// 	}
// 	return (*str);
// }

char	*next_token_word(char *str, t_token **new, int *error_code)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (*(str + i) && !is_wspace(*(str + i)) && !is_operator(*(str + i)))
	{
		if (*(str + i) == '\'' || *(str + i) == '\"')
		{
			while (*(str + i + j) && *(str + i + j) != *(str + i))
				j++;
			i += j;
			j = 1;
			if (!*(str + i))
				return (*error_code = 2, NULL);
		}
		i++;
	}
	*new = new_token(str, i);
	if (!*new)
		return (*error_code = 1, NULL);
	return (str + i);
}

// Identify and create the next token in a string
// It also pass the whitespace before and after the token
// Return value : a pointer to the string after the token
char	*next_token(char *str, t_token **new, int *error_code)
{
	while (*str && is_wspace(*str))
		str++;
	if (!*str)
		return (*error_code = 3, NULL);
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
		str = next_token_word(str, new, error_code);
	while (!*error_code && *str && is_wspace(*str))
		str++;
	return (str);
}

void	put_special_type_in_stack(t_token *stack)
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
}

// Affect a type to each node of the stack
void	put_type_in_stack(t_token *stack, int *error_code)
{
	(void)error_code;
	while (stack)
	{
		if (ft_strchr("|<>", stack->content[0]))
			put_special_type_in_stack(stack);
		else if (stack->content[0] == '&')
		{
			if (stack->content[1] == '&')
				stack->type = AND;
			else
				stack->type = INVALID;
		}
		else if (stack->content[0] == '(')
			stack->type = O_BRACKET;
		else if (stack->content[0] == ')')
			stack->type = C_BRACKET;
		else if (stack->content[0] == ';' || stack->content[0] == '\\')
			stack->type = INVALID;
		else
			stack->type = WORD;
		stack = stack->next;
	}
}

// Parse the prompt and create a stack (last element is first in stack)
// TODO: Change nomenclature of errors.
// Error codes: 0 : OK
//				1 : bad allocation
//				2 : ' or " not closed
//				3 : empty string
//				4 : problem with brackets ()
int	tokenise(char *str, t_token **stack)
{
	t_token	*new;
	int		error_code;

	new = NULL;
	error_code = 0;
	if (!*str)
		error_code = 3;
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
	if (check_syntax(stack))
		return (1);
	stack_copy = stack;
	i = 0;
	while (stack)
	{
		printf("TOKEN %d : \e[31m%s\e[0m%%\ttype : %d\tptr : %p\t"
			"prev ptr : %p\tnext ptr : %p\n", i,
			stack->content, stack->type, stack, stack->prev, stack->next);
		i++;
		stack = stack->next;
	}
	kill_stack(&stack_copy);
	return (error);
}*/
// gcc -g srcs/parsing/token.c srcs/parsing/check_syntax.c
// srcs/parsing/token_utils.c -I./include/ -I./libft/ -L./libft/ -lft -o token
