/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:46:46 by nrea              #+#    #+#             */
/*   Updated: 2024/03/18 16:42:23 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_variables.h"
#include "libft.h"
#include <stdio.h>

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

static int	ft_count_var(t_evar **vars)
{
	int		nb;
	int		i;
	t_evar	*var;

	nb = 0;
	i = 0;
	var = NULL;
	while (i < 58)
	{
		var = vars[i];
		while (var)
		{
			nb++;
			var = var->next;
		}
		i++;
	}
	return (nb);
}

/*concatenate the var in the form key=value*/
char	*ft_concatenate(t_evar *var)
{
	char	*ret;
	char	*ret2;

	ret = NULL;
	ret2 = NULL;
	if (!var || !var->key)
		return (NULL);
	ret = ft_strjoin(var->key, "=");
	if (!ret)
		return (NULL);
	if (!var->value)
		return (ret);
	ret2 = ft_strjoin(ret, var->value);
	free(ret);
	if (!ret2)
		return (NULL);
	return (ret2);
}

/*Arrange the env variables in the form of a null terminated
 char** array suitable for the envp parameter of execve*/
char	**ft_push_env_vars(t_evar **vars)
{
	int		var_nb;
	int		i;
	int		j;
	t_evar	*cur;
	char	**envp;

	i = 0;
	j = 0;
	var_nb = ft_count_var(vars);
	envp = malloc((var_nb + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	ft_memset(envp, 0, (var_nb + 1) * sizeof(char *));
	while (i < 58)
	{
		cur = vars[i];
		while (cur)
		{
			envp[j] = ft_concatenate(cur);
			if (!envp[j])
				return (ft_free_splitted(envp), NULL);
			j++;
			cur = cur->next;
		}
		i++;
	}
	return (envp);
}


