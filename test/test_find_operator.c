#include "parse_execute.h"
#include "tests.h"

//cc -g3  -Wall -Wextra -I./include -o test_find_operator  srcs/parsing/*.c
//test/utils/test_utils.c test/test_find_operator.c -I./libft  -L ./libft -lft -lreadline

int main()
{

	t_token	*stack;
	t_token	*right;
	t_token	*left;

	stack = NULL;
	right = NULL;
	left = NULL;

	// test_ft_add_token_lst(&stack, "&&", AND);
	test_ft_add_token_lst(&stack, "|", PIPE);
	test_ft_add_token_lst(&stack, "CMD1", WORD);
	// test_ft_add_token_lst(&stack, "||", OR);
	test_ft_add_token_lst(&stack, "CMD2", WORD);
	test_ft_add_token_lst(&stack, "CMD3", WORD);
	test_ft_add_token_lst(&stack, "CMD4", WORD);
	test_ft_add_token_lst(&stack, "CMD5", WORD);

printf("##########STACK####################\n");
	ft_display_stack_forward(stack);
	int priority = 2;
printf("rang du premier token de priorite %d [%d]\n", priority, ft_find_operator(priority,stack));
	 priority = 1;
printf("rang du premier token de priorite %d [%d]\n", priority, ft_find_operator(priority,stack));

		kill_stack(&stack);


	return (0);
}
