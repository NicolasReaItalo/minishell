

//////////////////////////////////////////////////////////////////////////
///////////       TEST SIMPLE DE ft_strip_bracket       //////////////////
//////////////////////////////////////////////////////////////////////////
/*cc -g3  -Wall -Wextra -I./include -o test_strip_brackets srcs/parsing/*.c test/utils/test_utils.c test/test_ft_strip_brackets.c
 -I./libft  -L ./libft -lft -lreadline*/


#include "parse_execute.h"
#include "tests.h"


int main()
{

	t_token	*stack;
	t_token	*right;
	t_token	*left;

	stack = NULL;
	right = NULL;
	left = NULL;

	test_ft_add_token_lst(&stack, ")",C_BRACKET);
	test_ft_add_token_lst(&stack, ")",C_BRACKET);
	test_ft_add_token_lst(&stack, "CMD1", WORD);
	test_ft_add_token_lst(&stack, "(",O_BRACKET);
	test_ft_add_token_lst(&stack, "CMD2", WORD);
	test_ft_add_token_lst(&stack, "CMD3", WORD);
	test_ft_add_token_lst(&stack, "(",O_BRACKET);


printf("##########STACK INITIALE####################\n");
	ft_display_stack(stack);

printf("##########APRES LE STRIP####################\n");
	stack = ft_strip_bracket(&stack);
	ft_display_stack_forward(stack);

		kill_stack(&stack);

	return (0);
}
