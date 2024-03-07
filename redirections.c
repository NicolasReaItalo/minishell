/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:47:22 by nrea              #+#    #+#             */
/*   Updated: 2024/03/07 18:33:55 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_utils.h"
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

/*returns the size of a line \n and non null terminated string*/
size_t	ft_get_ret_size(char *s)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	*ft_buffer_append(char *buf, char *line)
{
	char	*new_buf;
	int i;
	int j;

	new_buf = NULL;
	if (!buf)
	{
		buf = malloc(sizeof(char));
		if(!buf)
			return (NULL);
		buf[0] = '\0';
	}
	new_buf = malloc((ft_strlen(buf) + ft_strlen(line) + 1) * sizeof(char));
	if (!new_buf)
	{
		free(buf);
		return (NULL);
	}
	i = 0;
	while (buf[i])
	{
		new_buf[i] = buf[i];
		i++;
	}
	if (i != 0)
	{
		new_buf[i] = '\n';
		i++;
	}
	j = 0;
	while (line[j])
	{
		new_buf[i + j] = line[j];
		j++;
	}
	new_buf[i + j] = '\0';
	free(buf);
	return (new_buf);
}


int	ft_capture_here_doc(t_token *tok, char *eof)
{
	char	*line;

	if (!tok || tok->type != R_HEREDOC || !eof)
		return (-1);
	line = NULL;
	free(tok->content);
	tok->content= NULL;
	while(1)
	{
		line = readline(">");
		if(!line)
			break;
		if (!ft_strncmp(line, eof, sizeof(eof)))
		{
			free(line);
			if (!tok->content)
			{
				tok->content = malloc(sizeof(char));
				if(!tok->content)
					break ;
				tok->content[0] = '\0';
			}
			break ;
		}
		tok->content = ft_buffer_append(tok->content, line);
		free(line);
	}
	return (0);
}



//////////////////////////////////////////////////////////////////////////
int test_ft_add_token(t_token **stack, char *content, int type) //////A supprimer
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


void	ft_delete_token(t_token *token)
{
	t_token	*prev;
	t_token	*next;

	if (!token)
		return ;
	prev = token->prev;
	next = token->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(token->content);
	free(token);
}




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

t_token	*ft_get_last(t_token *stack)
{
	while (stack->next)
		stack = stack->next;
	return (stack);
}


void	ft_display_stack(t_token *stack)
{
	t_token	*node;
	int		rank;

	rank = 0;
	node = ft_get_last(stack);
	if (!node)
		printf("[NULL]\n");
	while (node)
	{
		printf("[%d]	type[%s]	content:[%s]\n", rank,type(node->type), node->content);
		node = node->prev;
		rank++;
	}
}







/// boucle principale
///Parcours le satck de la fin au debut
// si <<, capture le heredoc et le EOF puis stocke le buffer dans token.content
// supprime le token word suivant
// si <,stocke le content du token suivant comme fichier de redirection
// si >,stocke le content du token suivant comme fichier de redirection
// supprime le token word suivant
// si >>,stocke le content du token suivant comme fichier de redirection
int	ft_redirections(t_token **stack)
{
	t_token	*tok;
	t_token	*prev_tok;

	if (!*stack)
		return (-1);
	tok = ft_get_last(*stack);
	while (tok)
	{
		if (tok->type == R_HEREDOC)
		{
			prev_tok = tok->prev;
			ft_capture_here_doc(tok, prev_tok->content);
		}
		else if (tok->type >= 4 && tok->type <= 6)
		{
			free(tok->content);
			prev_tok = tok->prev;
			tok->content = ft_strdup(prev_tok->content);
		}
		tok = tok->prev;
	}
		return (0);
}
//destroys the words once their content is used by redirections
void	ft_clean_words(t_token *stack)
{
	t_token	*tok;
	t_token	*prev;

	tok = ft_get_last(stack);
	if (!tok)
		return ;
	while (tok)
	{
		if (tok->type >= 4 && tok->type <= 7)
		{
			prev = tok->prev;
			ft_delete_token(prev);
		}

		tok = tok->prev;
	}


}



int main()
{
	char *buffer;
	t_token	*stack;

	stack = NULL;
	buffer = NULL;
	test_ft_add_token(&stack, "EOF", WORD);
	test_ft_add_token(&stack, "<<",R_HEREDOC);
	test_ft_add_token(&stack, "file3", WORD);
	test_ft_add_token(&stack, ">>", R_APPEND);
	test_ft_add_token(&stack, "file2", WORD);
	test_ft_add_token(&stack, ">", R_OUT);
	test_ft_add_token(&stack, "file1", WORD);
	test_ft_add_token(&stack, "<", R_IN);
	test_ft_add_token(&stack, "EOF", WORD);
	test_ft_add_token(&stack, "<<", R_HEREDOC);
	printf("=============Avant redirections=============\n");
	ft_display_stack(stack);
	ft_redirections(&stack);
	printf("=============Apres redirections =============\n");
	ft_display_stack(stack);
		printf("=============Apres clean =============\n");
	ft_clean_words(stack); ///////////////////////// A REPARER !!!
	ft_display_stack(stack);
	kill_stack(&stack);

}
