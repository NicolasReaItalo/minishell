
//////////////////////////////////////////////////////////////////////////
///////////       TEST SIMPLE DE ft_redirections        //////////////////
//////////////////////////////////////////////////////////////////////////
/*cc -Wall -Wextra -o test_redirections srcs/parsing/here_doc.c  srcs/parsing/redirections.c
srcs/parsing/token_utils.c  ./test/utils/test_utils.c  srcs/parsing/token.c
srcs/parsing/check_syntax.c ./test/test_redirections.c
-g -I./include -I./libft -I ./test    -L ./libft -lft -lreadline */


#include "parser.h"
#include "tests.h"


int main()
{
	t_token	*stack;

	stack = NULL;
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
