

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
												// TEST ft_create_tree
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// /test du parser
///  cc -g   -Wall -Wextra -Werror  -o test_parse_tree  ./srcs/parsing/*.c  ./test/utils/test_utils.c ./test/test_ft_create_tree.c -I ./include -I./libft -I ./test  -L./libft  -lft -lreadline

#include "tests.h"







int main()
{

	t_node *tree;
	int		error;
	t_token	*stack;

	stack = NULL;
	tree  = NULL;

	error = 0;

	test_ft_add_token_lst(&stack, "cat", WORD);
	// test_ft_add_token_lst(&stack, "&&", AND);
	test_ft_add_token_lst(&stack, "||", OR);
	// test_ft_add_token_lst(&stack, "arg 3", WORD);
	// test_ft_add_token_lst(&stack, "cmd3", WORD);
	// test_ft_add_token_lst(&stack, "file 1", R_IN);
	// test_ft_add_token_lst(&stack, "&&", AND);
	// test_ft_add_token_lst(&stack, "(", C_BRACKET);
	test_ft_add_token_lst(&stack, "arg2", WORD);
	test_ft_add_token_lst(&stack, "here_doc", R_HEREDOC);
	test_ft_add_token_lst(&stack, "cmd2", WORD);
	test_ft_add_token_lst(&stack, "&&", AND);
	test_ft_add_token_lst(&stack, "arg1", WORD);
	test_ft_add_token_lst(&stack, "cmd1", WORD);
	// test_ft_add_token_lst(&stack, ")", O_BRACKET);

	tree = ft_create_tree(&stack, &error, 2);
	if (error)
	{
		printf("Error during tree creation %s\n", ft_handle_error(error));
		// kill_stack(&stack);
		ft_free_tree(tree);  ////////A ecrire
		return (1);
	}

	show_tree(tree, 0);  ////////A ecrire
	ft_free_tree(tree);  ////////A ecrire
}
