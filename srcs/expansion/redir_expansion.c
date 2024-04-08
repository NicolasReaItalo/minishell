/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joyeux <joyeux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:10:58 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/09 00:17:20 by joyeux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

int	contains_ifs_redir(char *str, char *ifs)
{
//	ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
//	if (!ifs)
//		return (0);
//	str = token->content;
	while (*str)
	{
		if (ft_strchr(ifs, *str))
			return (1);
		str++;
	}
	return (0);
}

int	count_valid_redir(char *content, t_token *token)
{
	DIR				*dir;
	struct dirent	*file;
	int				count;
	char			*str;

	dir = opendir(".");
	if (!dir)
		return (-1);
	count = 0;
	file = readdir(dir);
	while (file != NULL)
	{
		if (content[0] == '.' && content[1] == '/')
			str = content + 2;
		else
			str = content;
		//TODO: Pas sur de mon coup..., c'est bien content et pas file->d_name qui devrait m'indiquer si c'est un fichier cache
		// Revoir le parcours
		token->hidden = (str[0] == '.');
//		printf ("hidden value : %d\n", token->hidden);
//		printf("file %d : %s \n", count, str);
//		if (token->hidden)
//			printf("%s\t This is a hidden file\n", file->d_name);
//		else
//			printf("%s\t This is a normal file\n", file->d_name);
		if (token->hidden || file->d_name[0] !='.')
		{
			if (match_pattern(str, file->d_name))
			{
				count++;
				if (count == 1)
				{
					str = token->content;
					token->content = ft_strdup(file->d_name);
					free(str);
				}
			}
		}
		file = readdir(dir);
	}
//	printf ("number of files : %d\n", count);
	closedir(dir);
//	if (count == 1)
//		token
	return (count);
}

// expand the redir token
//	- strip the string from ifs
//	- si empty => error `$VAR: ambiguous redirect `
//	- strchr ifs => error
//	- si strchr *
//    	- count valid_pathnames si > 1 =>error
//    	- expand
// return an error code
int	expand_redir(t_token *token, t_shell *shell)
{
	char	*ifs;
	char	*str;
	char	*str2;

	str = expand_param_redir(token->content, shell);
	if (!str)
		return (1);
	ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	str2 = ft_strtrim(str, ifs);
	if (!str2[0])
	{
		ft_dprintf(2, "%s: ambiguous redirect\n ",token->content);
		return (5);
	}
	if (contains_ifs_redir(str2, ifs))
	{
		ft_dprintf(2, "%s: ambiguous redirect\n ",token->content);
		return (5);
	}
	if (ft_strchr(str2, '*'))
		if (count_valid_redir(str2, token) >= 2)
		{
			ft_dprintf(2, "%s: ambiguous redirect\n ",token->content);
			return (5);
		}
	ft_dprintf(2, "Value : %s", str2);
	return (0);
}

#include "minishell.h"
//#include "tests.h"
#include "token.h"
int	main(int argc, char **argv, char **envp)
{
	t_token *token;
	t_shell shell;

	if (!ft_init_env_vars(shell.env_vars, &shell.shell_vars))
		return (1);
	ft_fetch_env_vars(shell.env_vars, envp);
	token = new_token(argv[1], ft_strlen(argv[1]));
	expand_redir(token, &shell);
}
// gcc srcs/expansion/*.c srcs/env_variables/*.c srcs/parsing/*.c -I./include/ -I./libft/ -L./libft/ -lft -o redir_expansion