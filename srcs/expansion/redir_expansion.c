/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:10:58 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/10 13:33:00 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

int	contains_ifs_redir(char *str, char *ifs)
{
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
	char			*file_name;
	char			*tmp_name;
	

	dir = opendir(".");
	if (!dir)
		return (6);
	count = 0;
	file = readdir(dir);
	if (content[0] == '.' && content[1] == '/')
		str = content + 2;
	else
		str = content;
	while (file != NULL && count < 2)
	{
		file_name = ft_strdup(file->d_name);
		if (!file_name)
			return (6);
		token->hidden = (str[0] == '.');
		if (token->hidden || file_name[0] !='.')
		{
			if (match_pattern(str, file_name))
			{
				count++;
				tmp_name = ft_strdup(file_name);
			}
		}
		free(file_name);
		file = readdir(dir);
	}
//	printf ("number of files : %d\n", count);
	closedir(dir);
	if (count == 1)
	{
		free(token->content);
		token->content = tmp_name;
//		free(str);
	}
	if (count == 0)
	{
		free(token->content);
		token->content = ft_strdup(content);
	}
	
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
	int		error;

	str = expand_param_redir(token->content, shell);
	if (!str)
		return (1);
	ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	str2 = ft_strtrim(str, ifs);
	if (!str2)
		return (free(str), 1);
	free (str);
	if (!str2[0])
	{
		ft_dprintf(2, "%s: ambiguous redirect\n ",token->content);
		return (free(str2), 5);
	}
	if (contains_ifs_redir(str2, ifs))
	{
		ft_dprintf(2, "%s: ambiguous redirect\n ",token->content);
		return (free(str2), 5);
	}
//	if (ft_strchr(str2, '*'))
	error = count_valid_redir(str2, token);
	free(str2);
	if (error == 6)
		return (6);
	else if (error >= 2)
//		if (count_valid_redir(str2, token) >= 2)
	{
		ft_dprintf(2, "%s: ambiguous redirect\n ",token->content);
		return (5);
	}
//	ft_dprintf(2, "Value : %s", token->content);
	return (0);
}
/*
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
}*/
// gcc srcs/expansion/*.c srcs/env_variables/*.c srcs/parsing/*.c -I./include/ -I./libft/ -L./libft/ -lft -o redir_expansion