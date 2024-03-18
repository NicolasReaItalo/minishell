


#include "env_variables.h"
#include "libft.h"
#include <stdio.h>
#include "tests.h"

int main(int argc, char **argv, char **envp)
{

	t_evar	*vars[58];
	// char	*value = "chipmunks";

	ft_init_env_vars(vars);


	(void) argc;
	(void) argv;
	(void) envp;


	// var[0] = ft_create_var(key, value);
	// if (!var[0])
	// 	return (1);
	// var[57] = ft_create_var("zorglub", "nicolas");
	// if (!var[57])
		// return (1);
	// ft_set_var("zorglub", "moustache", vars);
	// ft_set_var("zorglub", "poilou", vars);
	// ft_set_var("zorglubo", "OOOOO", vars);////A regler
	// ft_set_var("zorgluba", "pedoncule", vars);
	// ft_set_var("a", "fuqhfeirufrei", vars);
	// ft_set_var("b", "fuqhfeirufrei", vars);
	// ft_set_var("c", "fuqhfeirufrei", vars);
	// ft_set_var("d", "fuqhfeirufrei", vars);
	// ft_set_var("e", "fuqhfeirufrei", vars);
	// ft_set_var("f", "fuqhfeirufrei", vars);
	// ft_set_var("g", "fuqhfeirufrei", vars);
	// ft_set_var("h", "fuqhfeirufrei", vars);
	// ft_set_var("i", "fuqhfeirufrei", vars);
	// ft_set_var("j", "fuqhfeirufrei", vars);
	// ft_set_var("k", "fuqhfeirufrei", vars);
	// ft_set_var("l", "fuqhfeirufrei", vars);
	// ft_set_var("m", "fuqhfeirufrei", vars);
	// ft_set_var("n", "fuqhfeirufrei", vars);
	// ft_set_var("o", "fuqhfeirufrei", vars);
	// ft_set_var("p", "fuqhfeirufrei", vars);
	// ft_set_var("q", "fuqhfeirufrei", vars);
	// ft_set_var("r", "fuqhfeirufrei", vars);
	// ft_set_var("s", "fuqhfeirufrei", vars);
	// ft_set_var("t", "fuqhfeirufrei", vars);
	// ft_set_var("u", "fuqhfeirufrei", vars);
	// ft_set_var("v", "fuqhfeirufrei", vars);
	// ft_set_var("w", "fuqhfeirufrei", vars);
	// ft_set_var("x", "fuqhfeirufrei", vars);
	// ft_set_var("y", "fuqhfeirufrei", vars);
	// ft_set_var("z", "fuqhfeirufrei", vars);
	// ft_set_var("_", "fuqhfeirufrei", vars);
	// ft_set_var("_fred", "fuqhfeirufrei", vars);
	// ft_set_var("_albert", "fuqhfeirufrei", vars);
	// ft_set_var("A", "fuqhfeirufrei", vars);
	// ft_set_var("B", "fuqhfeirufrei", vars);
	// ft_set_var("C", "fuqhfeirufrei", vars);
	// ft_set_var("D", "fuqhfeirufrei", vars);
	// ft_set_var("E", "fuqhfeirufrei", vars);
	// ft_set_var("F", "fuqhfeirufrei", vars);
	// ft_set_var("G", "fuqhfeirufrei", vars);
	// ft_set_var("H", "fuqhfeirufrei", vars);
	// ft_set_var("I", "fuqhfeirufrei", vars);
	// ft_set_var("J", "fuqhfeirufrei", vars);
	// ft_set_var("K", "fuqhfeirufrei", vars);
	// ft_set_var("L", "fuqhfeirufrei", vars);
	// ft_set_var("M", "fuqhfeirufrei", vars);
	// ft_set_var("N", "fuqhfeirufrei", vars);
	// ft_set_var("O", "fuqhfeirufrei", vars);
	// ft_set_var("P", "fuqhfeirufrei", vars);
	// ft_set_var("Q", "fuqhfeirufrei", vars);
	// // ft_set_var("R", "fuqhfeirufrei", vars);
	// ft_set_var("S", "fuqhfeirufrei", vars);
	// ft_set_var("T", "fuqhfeirufrei", vars);
	// ft_set_var("U", "fuqhfeirufrei", vars);
	// ft_set_var("V", "fuqhfeirufrei", vars);
	// ft_set_var("W", "fuqhfeirufrei", vars);
	// ft_set_var("X", "fuqhfeirufrei", vars);
	// ft_set_var("Y", "fuqhfeirufrei", vars);
	// ft_set_var("Z", "fuqhfeirufrei", vars);
	// ft_set_var("ZA", "fuqhfeirufrei", vars);
	// ft_set_var("ZB", "fuqhfeirufrei", vars);
	// ft_set_var("ZC", "fuqhfeirufrei", vars);


	// ft_set_var("SA", NULL, vars);
	// ft_set_var("SB", "seconde valeur", vars);
	// ft_fetch_env_vars(vars, envp);

	// ft_set_var("PATH", "DOUDDOU", vars);
	ft_set_var("nico", (char *)0, vars);
	ft_append_var("nico", "a", vars);
	ft_append_var("nico", "b", vars);
	ft_append_var("nico", "c", vars);
	ft_append_var("nico", "d", vars);
	ft_append_var("nico", "e", vars);
	ft_append_var("nico", "f", vars);
	ft_append_var("nico", "g", vars);
	ft_append_var("nico", "h", vars);
	ft_append_var("nico", "i", vars);
	ft_append_var("nico", "j", vars);
	ft_append_var("nico", "k", vars);
	ft_append_var("nico", "l", vars);
	ft_append_var("nico", "m", vars);
	ft_append_var("nico", "n", vars);
	ft_append_var("nico", "o", vars);
	ft_append_var("nico", "p", vars);
	ft_append_var("nico", "r", vars);
	ft_append_var("nico", "s", vars);
	ft_append_var("nico", "t", vars);
	ft_append_var("nico", "u", vars);
	ft_append_var("nico", "v", vars);
	ft_append_var("nico", "w", vars);
	ft_append_var("nico", "x", vars);
	ft_append_var("nico", "y", vars);
	ft_append_var("nico", "z", vars);
	// ft_set_var("nicolas", "deuxieme", vars);
	// ft_set_var("nicolaz", "troisieme", vars);
	ft_display_vars(vars);
	// ft_unset_var("nicolaz", vars);
	// ft_unset_var("nicolaz", vars);
	printf("\n\n\n*************************************** \n\n\n\n");





//test de la mise en split
	// char	**v;
	// v = NULL;
	// v = ft_push_env_vars(vars);
	// ft_display_char_vars(v);
	// ft_display_vars(vars);

	// ft_free_splitted(v);
	ft_free_env_vars(vars);

}





