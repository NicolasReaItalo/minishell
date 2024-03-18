/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:46:46 by nrea              #+#    #+#             */
/*   Updated: 2024/03/18 13:59:42 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
#include "libft.h"
#include <stdio.h>

int	ft_strcmp(char *s1, char *s2)
{
	while ((*s1 - *s2 == 0) && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	*ft_free_var(t_evar *var)
{
	if (!var)
		return (NULL);
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	free(var);
	return (NULL);
}

void	ft_free_env_vars(t_evar *env_list[58])
{
	int		i;
	t_evar	*prev;
	t_evar	*cur;

	i = 0;
	while (i < 58)
	{
		prev = NULL;
		cur = NULL;
		if (env_list[i])
		{
			cur = env_list[i];
			while (cur)
			{
				prev = cur;
				cur = cur->next;
				ft_free_var(prev);
			}
		}
		i++;
	}
}

/*allocate a var structure an initialize it with key and value*/
t_evar	*ft_create_var(char *key, char *value)
{
	t_evar	*var;

	if (!key || !key[0])
		return (NULL);
	var = NULL;
	var = malloc(sizeof(t_evar));
	if (!var)
		return (NULL);
	var->key = NULL;
	ft_memset(var, 0, sizeof(var));
	var->key = ft_strdup(key);
	if (!var->key)
		return (ft_free_var(var));
	var->value = NULL;
	var->next = NULL;
	if (value)
	{
		var->value = ft_strdup(value);
		if (!var->value)
			return (ft_free_var(var));
	}
	return (var);
}

/*Checks if the key  string is a valid key for an environement
variable
returns1 in cqse o success, 0 otherwise
RULES
no empty string
char : a-z or A-Z or 1-9 or _
first char must not be a  digit*/
int	ft_is_valid_key(char *key)
{
	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (*key)
	{
		if (!ft_isalpha(*key) && !ft_isdigit(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

/*get the value of the var identified by key
if the var doesn't exists  -> returns null */
t_evar	*ft_get_var(char *key, t_evar *sub_list)
{
	t_evar	*var;

	if (!ft_is_valid_key(key))
		return (NULL);
	var = NULL;
	var = sub_list;
	while (var)
	{
		if (!ft_strcmp(key, var->key))
			return (var);
		var = var->next;
	}
	return (NULL);
}

/*create a new var and place it at the right ascii order in the right stack*/
int	ft_create_and_place(char *key, char *value, t_evar **env_list)
{
	t_evar	*var;
	t_evar	*head;
	t_evar	*prev;

	var = NULL;
	var = ft_create_var(key, value);
	if (!var)
		return (0);
	head = *env_list;
	if (!head || ft_strcmp(head->key, key) > 0)
	{
		*env_list = var;
		var->next = head;
	}
	else
	{
		while (head && ft_strcmp(head->key, key) < 0)
		{
			prev = head;
			head = head->next;
		}
		var->next = head;
		prev->next = var;
	}
	return (1);
}

/*if the var exists => modify its value
else : create a new var and place it at the right spot*/
int	ft_set_var(char *key, char *value, t_evar **env_list)
{
	t_evar	*var;
	int		index;
	char	*val;

	val = NULL;
	if (!ft_is_valid_key(key))
		return (0);
	index = key[0] - 65;
	if (index < 0 || index > 57)
		return (0);
	var = ft_get_var(key, env_list[index]);
	if (!var)
		return (ft_create_and_place(key, value, &env_list[index]));
	else
	{
		if (value)
		{
			val = ft_strdup(value);
			if (!val)
				return (1);
		}
		free((var)->value);
		(var)->value = val;
	}
	return (1);
}

/*unset an env variable identifie by the key parameter*/
void	ft_unset_var(char *key, t_evar **vars)
{
	int		index;
	t_evar	*cur;
	t_evar	*prev;
	t_evar	*next;

	index = key[0] - 65;
	if (!ft_is_valid_key(key) || index < 0 || index > 57 || !vars[index])
		return ;
	cur = vars[index];
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
		{
			next = cur->next;
			ft_free_var(cur);
			if (prev)
				(prev)->next = next;
			else
				vars[index] = next;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}


/*get the value of the var identified by key
ifthe var doesn't exists or it's value is null -> returns ""*/
char	*ft_get_var_value(char *key, t_evar *env_list[58])
{
	int		index;
	t_evar	*var;

	if (!ft_is_valid_key(key) || !env_list)
		return ("");
	index = key[0] - 65;
	if (index < 0)
		return ("");
	var = env_list[index];
	while (var)
	{
		if (!ft_strcmp(key, var->key))
		{
			if (var->value)
				return (var->value);
			else
				return ("");
		}
		var = var->next;
	}
	return ("");
}

void	ft_display_vars(t_evar *vars[58])
{
	int		i;
	t_evar	*v;

	v = NULL;
	i = 0;
	while (i < 58)
	{
		if (vars[i])
		{
			v = vars[i];
			while (v)
			{
				printf("%s=%s\n", v->key, v->value);
				v = v->next;
			}
			v = NULL;
		}
		i++;
	}
}

void	*ft_free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
	return (NULL);
}

/*Fetch the environment variables from **envp
and store these in the shell vars structure*/
void	ft_fetch_env_vars(t_evar *vars[58], char **envp)
{
	char	**splitted;
	int		i;

	i = 0;
	while (envp[i])
	{
		splitted = ft_split(envp[i], '=');
		if (!splitted)
			return ;
		ft_set_var(splitted[0], splitted[1], vars);
		ft_free_splitted(splitted);
		splitted = NULL;
		i++;
	}
}


/*initialisation a 0 de la structure des varables d'environnement
probablement a regrouper avec une fonction d'initialisation
de toutes les variables de la structure shell */
void	ft_init_env_var(t_evar	*vars[58])
{
	ft_memset(vars, 0, 58 * sizeof(t_evar *));
}






/*
TODO

faire ft_push_env_vars-> pour passer a execve
expand()
field splitting()
cc -Wall -Wextra -Werror -g srcs/execution/env_variables.c -I./include -I./libft -Llibft -lft
*/




/*
VAR="ls -l"

$VAR

epansion -> ls -l
ifs ==> ls   -l


'$VAR'
expansion ==> '$VAR'
ifs ==>  '$VAR'
dequote ==> $VAR

"$VAR"
expansion ==> "ls -l"
ifs ==> "ls -l"
dequote ==> ls -l

*/



/*
EXEC



"$VAR -la"










*/



/*


int main(int argc, char **argv, char **envp)
{

	t_evar	*vars[58];
	// char	*value = "chipmunks";

	ft_init_env_var(vars);


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
	// ft_set_var("R", "fuqhfeirufrei", vars);
	ft_set_var("S", "fuqhfeirufrei", vars);
	ft_set_var("T", "fuqhfeirufrei", vars);
	ft_set_var("U", "fuqhfeirufrei", vars);
	ft_set_var("V", "fuqhfeirufrei", vars);
	ft_set_var("W", "fuqhfeirufrei", vars);
	ft_set_var("X", "fuqhfeirufrei", vars);
	ft_set_var("Y", "fuqhfeirufrei", vars);
	ft_set_var("Z", "fuqhfeirufrei", vars);
	ft_set_var("ZA", "fuqhfeirufrei", vars);
	ft_set_var("ZB", "fuqhfeirufrei", vars);
	ft_set_var("ZC", "fuqhfeirufrei", vars);


	// ft_set_var("SA", NULL, vars);
	// ft_set_var("SB", "seconde valeur", vars);
	// ft_fetch_env_vars(vars, envp);

	// ft_set_var("PATH", "DOUDDOU", vars);
	ft_set_var("nico", "froufrou", vars);
	ft_set_var("nicolas", "deuxieme", vars);
	ft_set_var("nicolaz", "troisieme", vars);
	ft_display_vars(vars);
	// ft_unset_var("nicolaz", vars);
	ft_unset_var("nicolaz", vars);
	printf("\n\n\nAPRES UNSET \n\n\n\n");
	ft_display_vars(vars);


	printf("nb de variables : [%d]", ft_count_var(vars));

	ft_free_env_vars(vars);

}


*/



