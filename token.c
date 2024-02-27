/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:23:26 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/02/27 18:28:38 by tjoyeux          ###   ########.fr       */
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
// Pass whitespace
// Identifie type du token
// Pass whitespace
// Return new pointer in string
char *next_token(char *str, t_token *new)
{
	int	i;
	
	i = 0;
	while (*str && is_whitespace(*str))
		str++;
	if (!*str)
		return (NULL);
	else if (is_operator(*str))
	{
		if (ft_strchr("|<>&", *str) && (*str == *(str + 1)))
		{
			new->content = ft_substr(str, 0, 2); 
			str++;
		}
		else
		new->content = ft_substr(str, 0, 1);
		str++; 
	}	
	else
	{
	// A implementer : Cas ou on a une chaine de caractere qui n'est pas un operateur
		while (*(str + i) && !is_whitespace(*(str + i)) && !is_operator(*(str + i)))
			i++;
		new->content = ft_substr(str, 0, i);
		str += i;	
	}
	while (*str && is_whitespace(*str))
		str++;
	return(str);
}

t_token	*add_token(t_token *stack, t_token *new)
{
	new->next = NULL;
	if (!stack)
		stack->next = new;
	else 
	{
		new->next = stack;
		stack->next = new;
	}
	return (stack);
}
// 1)Create node
// 2)Find
void	*tokenise(char *str, t_token **stack)
{
	t_token	*new;
	
	while (*str)
	{
		str = next_token(str, new);
		add_token(*stack, new); 
	}	
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
	
	stack = NULL;
	tokenise(argv[1], &stack);
	while (stack)
	{
		printf("TOKEN %d : %s%%\n", i, stack->content);
		i++;
	}
	return (0);
}
