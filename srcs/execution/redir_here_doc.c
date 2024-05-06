/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:21:42 by nrea              #+#    #+#             */
/*   Updated: 2024/05/06 15:51:26 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_execute.h"

static void	ft_putnbr_base_l(unsigned long nbr, char *base, char *file )
{
	unsigned long	base_len;
	unsigned long	tmp;
	unsigned long	div_value;
	int				i;

	i = 8;
	tmp = nbr;
	div_value = 1;
	base_len = ft_strlen(base);
	while (tmp)
	{
		tmp /= base_len;
		div_value *= base_len;
	}
	while (div_value >= 1)
	{
		file[i] = base[nbr / div_value];
		nbr %= div_value;
		div_value /= base_len;
		i++;
	}
}

/*Generate a unique here_doc filename in the form ms_hd_xxxx *where
xxx is the address of the content pointer*/
static char	*ft_generate_u_filename(char *content)
{
	char	*file;
	char	*tmp;

	if (!content)
		return (NULL);
	file = malloc (30 * sizeof(char));
	if (!file)
		return (NULL);
	ft_memset(file, 0, 30 * sizeof(char));
	ft_strcpy(file, "/tmp/ms_");
	ft_putnbr_base_l((unsigned long) content, "0123456789abcdef", file);
	while (!access(file, F_OK) && ft_strlen(file) < 255)
	{
		tmp = NULL;
		tmp = ft_strjoin(file, "x");
		free(file);
		file = tmp;
	}
	if (!access(file, F_OK))
	{
		free(file);
		return (NULL);
	}
	return (file);
}

static int	ft_exit(int is_error, char *file, int infile)
{
	if (is_error)
		perror(file);
	if (infile != -1)
		close(infile);
	if (file)
		free(file);
	return (is_error);
}

/*Apply the here_doc redirection by creating a tmp file, copying the hd_buffer
in it and redirect STDIN to it*/
int	ft_apply_r_heredoc(char *content)
{
	int		in_file;
	char	*file;

	file = NULL;
	in_file = -1;
	file = ft_generate_u_filename(content);
	if (!file)
	{
		write(2, "Here doc error!\n", 17);
		return (1);
	}
	in_file = open(file, O_WRONLY | O_CREAT, 0666);
	if (in_file == -1)
		return (ft_exit(1, file, in_file));
	if (write(in_file, content, ft_strlen(content)) == -1)
		return (ft_exit(1, file, in_file));
	close(in_file);
	in_file = open(file, O_RDONLY);
	if (in_file == -1)
		return (ft_exit(1, file, in_file));
	if (dup2(in_file, STDIN_FILENO) == -1)
		return (ft_exit(1, file, in_file));
	if (unlink(file) == -1)
		return (ft_exit(1, file, in_file));
	return (ft_exit(0, file, in_file));
}
