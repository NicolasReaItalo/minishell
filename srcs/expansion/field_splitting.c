/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:56:40 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/25 13:40:38 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"

// Create and add new tokens in a linked list
// Add content from a tab of char*
// Return 1 if error
int	words_to_token(t_token **ptr, char **words)
{
	t_token	*new;

	words++;
	while (*words)
	{
		new = malloc(sizeof(t_token));
		if (!new)
			return (1);
		ft_memset(new, 0, sizeof(t_token));
		new->content = ft_strdup(*words);
		new->next = (*ptr)->next;
		(*ptr)->next = new;
		*ptr = (*ptr)->next;
		words++;
	}
	return (0);
}

void	free_words_tab(char ***words)
{
	char	**original_words;

	original_words = *words;
	while (**words)
	{
		free(**words);
		**words = NULL;
		(*words)++;
	}
	free(original_words);
	original_words = NULL;
}

// Gestion de l'IFS apres l'expansion des parametres
// Return 0 ou code erreur
int	field_splitting(t_token *token, t_shell *shell, char *new)
{
	char	*ifs;
	char	**words;
	t_token	*ptr;
	char	*tmp;

	ifs = ft_get_var_value("IFS", shell->env_vars, shell->shell_vars);
	words = ft_split_multiple(new, ifs);
	if (!words)
		return (1);
	if (!words[0])
		return (free(words), 0);
	tmp = token->content;
	token->content = ft_strdup(*words);
	free (tmp);
	ptr = token;
	words_to_token(&ptr, words);
	free_words_tab(&words);
	return (0);
}
