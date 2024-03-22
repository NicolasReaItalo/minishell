/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:50:32 by nrea              #+#    #+#             */
/*   Updated: 2024/03/22 17:24:41 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "env_variables.h"


/*BROKEN!!!!! NE PAS UTILISER
ne prends pas en compte le prev*/
int	test_ft_add_token_front(t_token **stack, char *content, int type)
{
	t_token	*node;

	node = NULL;
	node = malloc (sizeof(t_token));
	if (!node)
		return (-1);
	node->content = ft_strdup(content);
	node->type = type;
	node->next = *stack;
	*stack = node;
	return (0);
}

int test_ft_add_token_lst(t_token **stack, char *content, int type)
{
	t_token *new_node;
	t_token *last_node;

	new_node = NULL;
	last_node = NULL;

	new_node = malloc (sizeof(t_token));
	if (!new_node)
		return (-1);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	new_node->type = type;
	if (!*stack)
	{
		new_node->prev = NULL;
		*stack = new_node;
		return (0);
	}
	last_node = *stack;
	while(last_node->next)
		last_node = last_node->next;
	new_node->prev = last_node;
	last_node->next = new_node;
	return (0);
}

//return the type as a str
char	*type(int type)
{
	if (type == 0)
		return ("WORD");
	if (type == 1)
		return ("|");
	if (type == 2)
		return ("&&");
	if (type == 3)
		return ("||");
	if (type == 4)
		return ("<");
	if (type == 5)
		return (">");
	if (type == 6)
		return (">>");
	if (type == 7)
		return ("<<");
	if (type == 8)
		return ("(");
	if (type == 9)
		return (")");
	return ("UNKNOWN");
}

// void	ft_display_stack_reverse(t_token *stack)
// {
// 	t_token	*node;
// 	int		rank;

// 	rank = 0;
// 	node = ft_get_token(stack, -1);
// 	if (!node)
// 		printf("[NULL]\n");
// 	while (node)
// 	{
// 		printf("[%d]	type[%s]	content:[%s]\n", rank,type(node->type), node->content);
// 		node = node->prev;
// 		rank++;
// 	}
// }

void	ft_display_stack_forward(t_token *stack)
{
	t_token	*node;
	int		rank;

	rank = 0;
	node = stack;
	if (!node)
		printf("[NULL]\n");
	while (node)
	{
		printf("[%d]	type[%s]	content:[%s]\n", rank,type(node->type), node->content);
		node = node->next;
		rank++;
	}
}

char *node_type(int type)
{
	if (type == N_EXEC)
		return ("EXEC");
	if (type == N_PIPE)
		return ("|");
	if (type == N_OR)
		return ("||");
	if (type == N_AND)
		return ("&&");
	return("");
}


void	show_tree(t_node *node, int i)
{
	int t;
	t_token	*display;

	if (!node)
		return ;
	if (node->type == 0)
	{
			t = i;
		while (t > 0)
		{
			ft_dprintf(1, "\t");
			t--;
		}
		ft_dprintf(1 ,"[%s] [cmd : ",node_type( node->type));
		display = node->cmd;
		while (display)
		{
				ft_dprintf(1 ,"{%s} ", display->content);
				display= display->next;
		}
		ft_dprintf(1 ,"]");
		ft_dprintf(1 ,"[redir : ");
		display =node->redir;
		while (display)
		{
				ft_dprintf(1 ,"{%s} ", display->content);
				display = display->next;
		}
		ft_dprintf(1 ,"]");
		ft_dprintf(1 ,"\n");
		return ;
	}
	t = i;
	while (t > 0)
	{
		ft_dprintf(1 ,"\t");
		t--;
	}
	ft_dprintf(1 ,"[%s] : \n", node_type(node->type));
	show_tree(node->right, i + 1);
	show_tree(node->left, i + 1);
}

/*Dislay all env variables in the env_vars array*/
void	ft_display_vars(t_evar *vars[58])
{
	int		i;
	t_evar	*v;

	v = NULL;
	i = 0;
	while (i < 58)
	{
		if (vars[i])
		{
			v = vars[i];
			while (v)
			{
				printf("%s=%s\n", v->key, v->value);
				v = v->next;
			}
			v = NULL;
		}
		i++;
	}
}

/*Dislay all env variables in the **envp char array*/
void	ft_display_char_vars(char **envp)
{
	int i = 0;

	if (!envp)
		return ;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}


