/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:23:26 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/02/28 16:39:43 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "libft/libft.h"

// Check if it's a whitespace
int	is_whitespace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));	
}
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&' || c == '(' || c == ')');
}
/*
int	error_msg(int i)
{
	return (i);		
}*/

t_token	*new_token(char *str, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));	
	if (!new)
//		error_msg(1);
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
char *next_token(char *str, t_token **new, int *error_code)
{
	int	i;
	
	i = 0;
	while (*str && is_whitespace(*str))
		str++;
	if (!*str)
		return (*error_code = 2, NULL);
	else if (*str == 34 || *str == 39)
	{
		while (*(str + ++i) && *(str + i) != *str)
			{};
		if (!*(str + i)) // Cas ou les guillemets ne sont pas fermes
			return (*error_code = 2, NULL);
		i++;
		*new = new_token(str, i);
		if (!*new)
			return (*error_code = 1, NULL);
		str += i;
//		TODO: Gerer le cas ou les guillemetsne sont pas refermes
	}
	else if (is_operator(*str))
	{
		if (ft_strchr("|<>&", *str) && (*str == *(str + 1)))
		{
			*new = new_token(str, 2);
		//	new->content = ft_substr(str, 0, 2); 
			str++;
		}
		else
		{
			*new = new_token(str, 1);
		}
		if (!*new)
			return (*error_code = 1, NULL);
	//	new->content = ft_substr(str, 0, 1);
		str++; 
	}	
	else
	{
		while (*(str + i) && !is_whitespace(*(str + i)) && !is_operator(*(str + i)))
			i++;
		*new = new_token(str, i);
		if (!*new)
			return (*error_code = 1, NULL);
//		new->content = ft_substr(str, 0, i);
		str += i;	
	}
	while (*str && is_whitespace(*str))
		str++;
	return(str);
}

t_token	*add_token(t_token *stack, t_token *new)
{
//	new = NULL;
	if (!stack)
		stack = new;
	else 
	{
		new->next = stack;
		stack = new;
	}
	return (stack);
}
// 1)Create node
// 2)Find
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
			return (error_code);
		if (new)
			*stack = add_token(*stack, new); 
	}
	return (error_code);	
}
/*
t_token	*tokenise(char *str)
{
	char	*p;
	int		i;
	char	*s;
	t_token	*stack;
	
	
	while(is_whitespace(*str))
		str++;
	p = str;
		i = 0;
	stack = NULL;
	while (*(p + i) && !is_operator(*(p + i))&& !is_whitespace(*(p+ i))) 
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

#include <stdio.h>
int	main(int argc,char **argv)
{
	int	i;
	t_token *stack;
	int error;
//	char arg[] = "ec\"h'o\"'";
	
	if (argc != 2)
		return (1);
	
	stack = NULL;
	if (error = tokenise(argv[1], &stack))
		return (error);
	i = 0;
	while (stack)
	{
		printf("TOKEN %d : %s%%\n", i, stack->content);
		i++;
		stack = stack->next;
	}
	return (error);
}
