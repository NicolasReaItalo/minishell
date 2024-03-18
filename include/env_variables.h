/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:40:05 by nrea              #+#    #+#             */
/*   Updated: 2024/03/18 17:17:43 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VARIABLES_H
#define ENV_VARIABLES_H
# include <stdlib.h>

//variables d'envionnement classique
typedef struct	s_evar
{
	char			*key;
	char			*value;
	struct	s_evar	*next;
}				t_evar;

// variables de shells speciales
typedef struct s_s_ars
{
	char	*ifs; // a initialiser avec " \t\n"
	int		exit_code; // a initialiser a 0
} t_svars;


char	*ft_get_var_value(char *key, t_evar *env_list[58]);
int		ft_set_var(char *key, char *value, t_evar **env_list);
int		ft_append_var(char *key, char *value, t_evar **env_list);
void	ft_unset_var(char *key, t_evar **vars);
void	ft_init_env_var(t_evar	*vars[58]);
void	ft_fetch_env_vars(t_evar *vars[58], char **envp);
char	**ft_push_env_vars(t_evar **vars);
void	ft_free_env_vars(t_evar *env_list[58]);

#endif
