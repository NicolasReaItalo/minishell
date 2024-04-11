/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:10:58 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/11 17:29:02 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

static int	find_valid_files(t_token *token, struct dirent *file
	, char *content, char **tmp_name)
{
	char	*file_name;
	char	*str;

	if (content[0] == '.' && content[1] == '/')
		str = content + 2;
	else
		str = content;
	file_name = ft_strdup(file->d_name);
	if (!file_name)
		return (6);
	token->hidden = (str[0] == '.');
	if (token->hidden || file_name[0] != '.')
	{
		if (match_pattern(str, file_name))
		{
			if (token->nb_files == 0)
				*tmp_name = ft_strdup(file_name);
			(token->nb_files)++;
		}
	}
	free(file_name);
	return (0);
}

static void	files_found(t_token *token, char **tmp_name)
{
	if (token->nb_files == 1)
	{
		free(token->content);
		token->content = *tmp_name;
	}
	else
		free(*tmp_name);
}

int	count_valid_redir(char *content, t_token *token)
{
	DIR				*dir;
	struct dirent	*file;
	char			*tmp_name;

	dir = opendir(".");
	if (!dir)
		return (6);
	token->nb_files = 0;
	file = readdir(dir);
	while (file != NULL && token->nb_files < 2)
	{
		if (find_valid_files(token, file, content, &tmp_name))
			return (1);
		file = readdir(dir);
	}
	closedir(dir);
	if (token->nb_files == 0)
	{
		free(token->content);
		token->content = ft_strdup(content);
	}
	else
		files_found(token, &tmp_name);
	return (token->nb_files);
}

// expand the redir token
//	- strip the string from ifs
//	- si empty => error `$VAR: ambiguous redirect `
//	- strchr ifs => error
//	- si strchr *
//    	- count valid_pathnames si > 1 =>error
//    	- expand
// return an error code
static int	ambiguous_redirect(char *content)
{
	ft_putstr_fd(content, 2);
	ft_putstr_fd(": ambiguous redirect\n ", 2);
	return (5);
}

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
		return (free(str2), ambiguous_redirect(token->content));
	if (contains_ifs_redir(str2, ifs))
		return (free(str2), ambiguous_redirect(token->content));
	error = count_valid_redir(str2, token);
	free(str2);
	if (error == 6)
		return (6);
	else if (error >= 2)
		return (ambiguous_redirect(token->content));
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