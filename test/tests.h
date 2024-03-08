#ifndef TEST_H
# define TEST_H

#include "parser.h"
/*test/utils/test_utils.c*/

int	test_ft_add_token_front(t_token **stack, char *content, int type);
int test_ft_add_token_lst(t_token **stack, char *content, int type);
void	ft_display_stack_forward(t_token *stack);
void	ft_display_stack_reverse(t_token *stack);
#endif
