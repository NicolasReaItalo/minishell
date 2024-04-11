
#include "parse_execute.h"
#include "tests.h"

/// TEST DE split_token_lst

/*cc -g3  -Wall -Wextra -I./include -o test_split_token_list
 srcs/parsing/*.c test/utils/test_utils.c
 test/test_split_token_lst.c -I./libft  -L ./libft -lft -lreadline*/
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
	test_ft_add_token_lst(&stack, "CMD1", WORD);
	test_ft_add_token_lst(&stack, "||", OR);
	test_ft_add_token_lst(&stack, "CMD2", WORD);
	test_ft_add_token_lst(&stack, "CMD3", WORD);
	test_ft_add_token_lst(&stack, "CMD4", WORD);
	test_ft_add_token_lst(&stack, "CMD5", WORD);

printf("##########STACK INITIALE####################\n");
	ft_display_stack_forward(stack);
int retour;
	retour = split_token_lst(4, &stack, &left, &right);
printf("Retour de split [%d]\n", retour);
printf("##########APRES LE SPLIT####################\n");
printf("#########left\n");
	ft_display_stack_forward(left);
printf("#########right\n");
	ft_display_stack_forward(right);

	if (retour == -1)
		kill_stack(&stack);

	kill_stack(&left);
	kill_stack(&right);


	return (0);
}

