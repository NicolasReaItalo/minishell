/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:16:22 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/08 17:41:22 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_tree(t_node *node, int i)
{
	if (node->type == 0)
	{
		while (i > 0)
		{
			ft_printf("\t");
			i--;
		} 
		ft_printf("->type %d : ", node->type);
		while (node->cmd)
		{
				ft_printf("%s ", node->cmd->content);
				node->cmd = node->cmd->next;
		}
		ft_printf("\n");
		return ;
	}
	while (i > 0)
	{
		ft_printf("\t");
		i--;
	}
	ft_printf("->type %d : ", node->type);
	show_tree(node->left, i++);
	show_tree(node->right, i++);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	
	show_tree(node, 0);
	return (0);
}
