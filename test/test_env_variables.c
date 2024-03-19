


#include "env_variables.h"
#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include "tests.h"

int main(int argc, char **argv, char **envp)
{

	t_shell	shell;

	ft_init_env_vars(shell.env_vars, &shell.shell_vars);


	(void) argc;
	(void) argv;


	ft_fetch_env_vars(shell.env_vars, envp);

	printf("PATH=%s", ft_get_var_value("PATH", shell.env_vars, shell.shell_vars));

	ft_free_env_vars(shell.env_vars, &shell.shell_vars);

}





