/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:40:05 by nrea              #+#    #+#             */
/*   Updated: 2024/03/19 13:59:14 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VARIABLES_H
# define ENV_VARIABLES_H
# include <stdlib.h>
# include "libft.h"
//variables d'envionnement classique
typedef struct s_evar
{
	char			*key;
	char			*value;
	struct s_evar	*next;
}	t_evar;

/*
variables de shells speciales
ifs =  a initialiser avec " \t\n"
EXIT_STATUS :  a initialiser a "0"*/
typedef struct s_s_ars
{
	char	*ifs;
	char	*exit_code;
}	t_svars;

int		ft_set_var(char *key, char *value, t_evar **env_list, t_svars *svars);
t_evar	*ft_create_var(char *key, char *value);
t_evar	*ft_get_var(char *key, t_evar *sub_list);
int		ft_create_and_place(char *key, char *value, t_evar **env_list);
int		ft_get_index(char first_letter, int *index);

void	ft_unset_var(char *key, t_evar **vars);
char	*ft_get_var_value(char *key, t_evar	*env_vars[58], t_svars shell_vars);
int		ft_append_var(char *key, char *value, t_evar **env_l, t_svars *svars);

char	**ft_push_env_vars(t_evar **vars);
void	ft_fetch_env_vars(t_evar *vars[58], char **envp);

int		ft_init_env_vars(t_evar	*vars[58], t_svars *shell_vars);
void	*ft_free_var(t_evar *var);
void	ft_free_env_vars(t_evar *env_list[58], t_svars *shell_vars);
void	*ft_free_splitted(char **splitted);
int		ft_is_valid_key(char *key);

int		ft_isshell_var(char *key);
char	*ft_get_shell_var(char *key, t_svars shell_vars);
int		ft_set_shell_var(char *key, char *value, t_svars *svars);
int		ft_append_s_var(char *key, char *value, t_evar **env_l, t_svars *svars);

int		ft_get_exit_status(t_svars *svars);
int		ft_set_exit_status(int status, t_svars *svars);
#endif
