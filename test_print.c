/*

Petit programme simple qui affiche les
arguments et les variables d'environement heritees
pour debugger minishell


*/

#include <stdio.h>
#include "libft.h"
#define KCYN  "\x1B[36m"

int main(int argc, char **argv, char **env)
{
	int i = 0;
	ft_dprintf(1, KCYN);
	ft_dprintf(1, "=============pgm arguments=============\n");
	while (i < argc)
	{
		printf("%s\n", argv[i]);
		i++;
	}
	ft_dprintf(1,"=============pgm env var=============\n");
	i = 0;
	while (env[i])
	{

		ft_dprintf(1,"%s\n", env[i]);
		i++;
	}
	ft_dprintf(1,"\033[0m");
	return 0;
}
