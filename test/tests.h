#ifndef TEST_H
# define TEST_H

#include "parse_execute.h"
#include "env_variables.h"

/*test/utils/test_utils.c*/

int	test_ft_add_token_front(t_token **stack, char *content, int type);
int test_ft_add_token_lst(t_token **stack, char *content, int type);
void	ft_display_stack_forward(t_token *stack);
void	show_tree(t_node *node, int i);
void	ft_display_char_vars(char **envp);
void	ft_display_vars(t_evar *vars[58]);
// void	*ft_free_splitted(char **splitted);
#endif
