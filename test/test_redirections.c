
//////////////////////////////////////////////////////////////////////////
///////////       TEST SIMPLE DE ft_redirections        //////////////////
//////////////////////////////////////////////////////////////////////////

#include "parser.h"
#include "tests.h"


int main()
{
	char *buffer;
	t_token	*stack;

	stack = NULL;
	buffer = NULL;
	test_ft_add_token_lst(&stack, "arg2", WORD);
	test_ft_add_token_lst(&stack, "EOF", WORD);
	test_ft_add_token_lst(&stack, "<<",R_HEREDOC);
	test_ft_add_token_lst(&stack, "file3", WORD);
	test_ft_add_token_lst(&stack, ">>", R_APPEND);
	test_ft_add_token_lst(&stack, "file2", WORD);
	test_ft_add_token_lst(&stack, ">", R_OUT);
	test_ft_add_token_lst(&stack, "file1", WORD);
	test_ft_add_token_lst(&stack, "<", R_IN);
	test_ft_add_token_lst(&stack, "arg1", WORD);
	test_ft_add_token_lst(&stack, "cmd1", WORD);
	test_ft_add_token_lst(&stack, "EOF", WORD);
	test_ft_add_token_lst(&stack, "<<", R_HEREDOC);
	printf("=============Avant redirections=============\n");
	ft_display_stack(stack);
	ft_redirections(&stack);
	printf("=============Apres redirections =============\n");
	ft_display_stack(stack);
	kill_stack(&stack);

}
