/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:56:40 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/05/01 11:07:25 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

// Create and add new tokens in a linked list
// Add content from a tab of char*
// Return 1 if error
int	words_to_token(t_token *ptr, char **words, int i)
{
	t_token	*new;

	words++;
	while (*words)
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return (1);
		ft_memset(new, 0, sizeof(t_token));
		if (i == 1)
			new->param_expanded = 1;
		else if (i == 2)
			new->path_expanded = 1;
		new->content = ft_strdup(*words);
		new->next = ptr->next;
		ptr->next = new;
		ptr = ptr->next;
		words++;
	}
	return (0);
}

int	get_last_word(char **words)
{
	int	i;

	if (!*words)
		return (-1);
	i = 0;
	while (words[i] != NULL)
		i++;
	return (i - 1);
}
// Gestion de l'IFS apres l'expansion des parametres
// Return 0 ou code erreur
int	field_splitting(t_token *token, char *start, char *end)
{
//	char	*ifs;
	char	**words;
	t_token	*ptr;
//	int		last;
//	char	*tmp;
	char	*tmp2;

//	ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	words = ft_split(token->content, -1);
	ptr = token;
	if (words == NULL)
		return (1);
/*	if (words[0])
	{
		last = get_last_word(words);
		if (last == -1)
			return (free(words), 0);
		tmp2 = ft_strjoin(start, words[0]); // a proteger
		tmp = ft_strjoin(words[last], end); // a proteger
		free (words[last]);
		words[last] = tmp;
	}*/
//	else
	// Cas ou il n'y a que des caracteres ifs
	if (!words[0])
	{
		free_words_tab(&words);
		words = malloc(3 * sizeof(char*)); // a proteger
		tmp2 = ft_strdup(start);
		words[0] = ft_strdup("");
		words[1] = ft_strdup(end);
		words[2] = NULL;
	}
	else
		tmp2 = ft_strdup(words[0]);
	words_to_token(ptr, words, 1); // a proteger
	free_words_tab(&words);
	free(token->content);
	token->content = tmp2;
	return (0);
}
