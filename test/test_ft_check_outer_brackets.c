#include "parse_execute.h"
#include "tests.h"




///
/// cc -g3  -Wall -Wextra -I./include -o test_check_outer_brackets srcs/parsing/*.c
/// test/utils/test_utils.c test/test_ft_check_outer_brackets.c -I./libft  -L ./libft -lft -lreadline
///


int main()
{

	t_token	*stack;
	t_token	*right;
	t_token	*left;

	stack = NULL;
	right = NULL;
	left = NULL;

	test_ft_add_token_lst(&stack, "&&", AND);
	test_ft_add_token_lst(&stack, "|", PIPE);
	test_ft_add_token_lst(&stack, "(",O_BRACKET);
	test_ft_add_token_lst(&stack, "CMD1", WORD);
	test_ft_add_token_lst(&stack, "||", OR);
	test_ft_add_token_lst(&stack, ")",C_BRACKET);
	test_ft_add_token_lst(&stack, "CMD2", WORD);
	test_ft_add_token_lst(&stack, "CMD3", WORD);
	test_ft_add_token_lst(&stack, "CMD4", WORD);
	test_ft_add_token_lst(&stack, "CMD5", WORD);


printf("##########STACK ####################\n");
	ft_display_stack_forward(stack);


	printf("retour de check_outer_brackets [%d] \n", ft_check_outer_brackets(stack) );

		kill_stack(&stack);

	return (0);
}
