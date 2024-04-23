/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multiple.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:55:45 by nrea              #+#    #+#             */
/*   Updated: 2024/04/23 15:25:19 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

int	ft_is_separator(char c, char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

int	ft_count_words(char *str, char *charset)
{
	int		word_nb;
	int		new_word;
	char	*in_quotes;

	word_nb = 0;
	new_word = 1;
	in_quotes = NULL;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			in_quotes = str;
			str++;
			while (*str && *str != *in_quotes)
				str++;
			if (*str == *in_quotes)
				str++;
		}
		if (ft_is_separator(*str, charset))
			new_word = 1;
		else if (new_word)
		{
			word_nb++;
			new_word = 0;
		}
		str++;
	}	
	return (word_nb);
}

int	ft_get_word_size(char *word, char *charset)
{
	int	i;

	i = 0;
	while (!ft_is_separator(word[i], charset) && word[i])
		i++;
	return (i);
}

char	*ft_add_word(char *str, int word_size)
{
	char	*word;
	int		i;

	word = (char *) malloc((word_size + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (i < word_size && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_multiple(char *str, char *charset)
{
	char	**split;
	int		size;
	int		i;
	char	*in_quotes;
	char	*original_str;

	i = 0;
	size = ft_count_words(str, charset) + 1;
	split = malloc(size * sizeof(char *));
	if (!split)
		return (NULL);
	while (*str)
	{		
		original_str = str;
		if (*str == '\'' || *str == '\"')
		{
			in_quotes = str;
			str++;
			while (*str && *str != *in_quotes)
				str++;
			if (*str == *in_quotes)
				str++;
		}
		if (ft_is_separator(*str, charset))
			str++;
		else
		{
			split[i] = ft_add_word(original_str, ft_get_word_size(str, charset));
			if (!split[i])
				return (NULL);
			while (!ft_is_separator(*str, charset) && *str)
				str++;
		i++;
		}
	}
	split[i] = 0;
	return (split);
}
/*
#include<stdio.h>
int main()
{
	char	**split;

split = ft_split("ABC DEF"," ");


int i = 0;
while(split[i])
{
if (split[i] == 0)
	break;
printf("%s\n",split[i]);
i++;
}


i = 0;
while (split[i])
{
free(split[i]);
i++;
}

free(split);
return 0;
}*/
