/*

Petit programme simple qui affiche les
arguments et les variables d'environement heritees
pour debugger minishell


*/

#include <stdio.h>
#define KCYN  "\x1B[36m"

int main(int argc, char **argv, char **env)
{
	int i = 0;
printf(KCYN);
printf("=============pgm arguments=============\n");
	while (i < argc)
	{
		printf("%s\n", argv[i]);
		i++;
	}
printf("=============pgm env var=============\n");
	i = 0;
	while (env[i])
	{

		printf("%s\n", env[i]);
		i++;
	}
	printf("\033[0m");
	return 0;
}
