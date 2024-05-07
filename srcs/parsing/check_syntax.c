/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:21:18 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/07 13:24:57 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

void	syntax_error(char *error)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("'\n", 2);
}

static char	*check_start_and_end(t_token *ptr)
{
	if (!ptr->next)
	{
		if ((ptr->type > 0 && ptr->type < 8) || ptr->type == 9)
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

static char	*check_syntax_node(t_token *ptr, t_token *stack, t_shell *shell)
{
	int	prev_type;

	if (!ptr)
		return (NULL);
	if (ptr->type == -1)
		return (ptr->content);
	if (!ptr->next && ((ptr->type > 0 && ptr->type < 4) || ptr->type == 9))
		return (ptr->content);
	if (!ptr->prev)
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
	else if (ptr->type == 7 && manage_heredoc(ptr, &stack, shell))
			return ("");
	else if ((ptr->type == 0) && (prev_type == 8))
		return (ptr->prev->content);
	else if ((ptr->type == 9)
		&& !(prev_type == 2 || prev_type == 3 || prev_type == 9))
		return (ptr->prev->content);
	return (NULL);
}

int	check_syntax(t_token *stack, t_shell *shell)
{
	t_token	*ptr;
	char	*error;
	int		check_brackets;

	ptr = ft_get_token(stack, -1);
	check_brackets = 0;
	while (ptr)
	{
		error = check_syntax_node(ptr, stack, shell);
		if (error && !error[0])
			return (130);
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
		return (ft_putstr_fd("syntax error : brackets unclosed\n", 2), 1);
	return (0);
}
