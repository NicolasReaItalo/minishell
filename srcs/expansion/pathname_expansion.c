/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:29:47 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/04/01 17:41:03 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "word_expansion.h"
#include <stdio.h>

// Verifie si le nom du fichier est conforme au format de l'expansion
static int is_valid_pathname(char *pathname, char *word)
{
	while (*word)
	{
		while (*pathname == '*' && *word)
		{
			while (*(pathname +1) == '*')
				pathname++; 
			while (*word && *(pathname + 1) != *word)
				word++;
			if (!*word && !*(pathname + 1))
				return (1);
			else if (!*word)
				return (0);
			pathname++;
		}	
		if (*pathname != *word)
			return (0);
		pathname++;
		word++;
	}
	if (!*pathname)
		return (1);
	return (0);
}

// 
void show_directory(char *pathname)
{
	DIR	*dir;
	struct dirent	*file;
	
	dir = opendir(".");
	if (!dir)
		return ;
	while ((file = readdir(dir)) != NULL)
	{
		if (is_valid_pathname(pathname, file->d_name))
			printf("%s\n", file->d_name);
	}
	closedir(dir);
}

//# include <stdio.h>
int	main(int argc, char **argv)
{
//	show_directory();
/*	if (argc == 3)
	{
		if (is_valid_pathname(argv[1], argv[2]))
			printf("Valid pathname\n");
		else
			printf("Invalid pathname\n");
	}*/
	show_directory(argv[1]);
	return (0);
}
// gcc -g3 srcs/expansion/pathname_expansion.c -I./include -I./libft -o pathname_expansion