/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <tjoyeux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:52:18 by tjoyeux           #+#    #+#             */
/*   Updated: 2024/03/11 13:22:29 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void test_command(char *input, char *expected_output)
{
	char *output;

	output = parsing(input);
	if (ft_strncmp(output, expected_output, ft_strlen(output)) == 0)
		ft_printf("\nThe output correspond to what's expected\n");
	else
		ft_printf("\nError\n\texpected : %s\n\trendered : %s\n");
}

int	main(void)
{
	test_command("(cmd1 arg1 && cmd2 <<EOF arg2 ) && <file1 cmd3 arg3 || cat", "[||] : \n[EXEC] [cmd : cat ][redir : ]\n[&&] : \n\t[EXEC] [cmd : cmd3 arg 3 ][redir : file 1 ]\n\t[&&] : \n\t\t[EXEC] [cmd : cmd2 arg2 ][redir : here_doc ]\t\t[EXEC] [cmd : cmd1 arg1 ][redir : ]");
}