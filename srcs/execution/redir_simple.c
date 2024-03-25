/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_simple.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:15:35 by nrea              #+#    #+#             */
/*   Updated: 2024/03/25 17:16:01 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*Apply the redirection of the outfile in TRUNC_MODE
	return 0 in case of success or the error code to output 1 */
int	ft_apply_r_out(char *file)
{
int	out_file;

out_file = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
if (out_file == -1)
{
	perror(file);
	return(1);
}
if (dup2(out_file, STDOUT_FILENO) == -1)
{
	close(out_file);
	return(1);
}
	close(out_file);
	return (0);
}

/*Apply the redirection of the outfile in APPEND_MODE
	return 0 in case of success or the error code to output 1 */
int	ft_apply_r_append(char *file)
{
int	out_file;

out_file = open(file, O_CREAT | O_APPEND | O_WRONLY, 0666);
if (out_file == -1)
{
	perror(file);
	return(1);
}
if (dup2(out_file, STDOUT_FILENO) == -1)
{
	close(out_file);
	return(1);
}
	close(out_file);
	return (0);
}

/*Apply the redirection of the infile
	return 0 in case of success or the error code to output : 1 */
int	ft_apply_r_in(char *file)
{
int	in_file;

in_file = open(file, O_RDONLY);
if (in_file == -1)
{
	perror(file);
	return(1);
}
if (dup2(in_file, STDIN_FILENO) == -1)
{
	close(in_file);
	return(1);
}
	close(in_file);
	return (0);
}
