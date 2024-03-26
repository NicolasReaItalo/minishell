/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:52 by nrea              #+#    #+#             */
/*   Updated: 2024/03/26 14:01:44 by nrea             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*Handling of redirects : return 0 if success or -1 in
case of failure*/
int	ft_apply_redir(t_node *node)
{
	t_token	*redir;
	int		ret;

	ret = 0;
	redir = node->redir;
	while (redir)
	{
		if (redir->type == R_OUT)
			ret = ft_apply_r_out(redir->content);
		else if (redir->type == R_IN)
			ret = ft_apply_r_in(redir->content);
		else if (redir->type == R_APPEND)
			ret = ft_apply_r_append(redir->content);
		else if (redir->type == R_HEREDOC)
			ret = ft_apply_r_heredoc(redir->content);
		if (ret)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

static int	ft_ret_dup_pipe_err(t_shell *shell)
{
	ft_display_error_msg(NULL, "Internal Error\n");
	ft_close_pipe_ar(shell->pipe_ar.pipes, shell->pipe_ar.pipes_nb);
	ft_free_pipe_ar(shell->pipe_ar.pipes, shell->pipe_ar.pipes_nb);
	return (-1);
}

/*Apply the redirections of the pipes in a exec node
this function is only triggered if pipe_lvl > -1*/
int	ft_apply_pipe_redir(t_node *node, int p_lvl, t_shell *s)
{
	if (node->side == left)
	{
		if (dup2(s->pipe_ar.pipes[p_lvl][1], STDOUT_FILENO) == -1)
			return (ft_ret_dup_pipe_err(s));
	}
	else if (node->side == right)
	{
		if (dup2(s->pipe_ar.pipes[p_lvl][0], STDIN_FILENO) == -1)
			return (ft_ret_dup_pipe_err(s));
		if (p_lvl > 0)
		{
			if (dup2(s->pipe_ar.pipes[p_lvl - 1][1], STDOUT_FILENO) == -1)
				return (ft_ret_dup_pipe_err(s));
		}
	}
	ft_close_pipe_ar(s->pipe_ar.pipes, s->pipe_ar.pipes_nb);
	ft_free_pipe_ar(s->pipe_ar.pipes, s->pipe_ar.pipes_nb);
	return (0);
}
