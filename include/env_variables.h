/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:40:05 by nrea              #+#    #+#             */
/*   Updated: 2024/03/18 18:48:39 by nrea             ###   ########.fr       */
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
	char	*exit_code; // a initialiser a "0"
} t_svars;

int		ft_set_var(char *key, char *value, t_evar **env_list);
int		ft_append_var(char *key, char *value, t_evar **env_list, t_svars *svars);

void	ft_unset_var(char *key, t_evar **vars);
char	*ft_get_var_value(char *key, t_evar	*env_vars[58], t_svars shell_vars);

char	**ft_push_env_vars(t_evar **vars);
void	ft_fetch_env_vars(t_evar *vars[58], char **envp);

int		ft_init_env_vars(t_evar	*vars[58], t_svars *shell_vars);
void	*ft_free_var(t_evar *var);
void	ft_free_env_vars(t_evar *env_list[58], t_svars *shell_vars);
void	*ft_free_splitted(char **splitted);
int		ft_is_valid_key(char *key);
#endif
