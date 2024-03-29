/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrea <nrea@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:59:52 by nrea              #+#    #+#             */
/*   Updated: 2024/03/29 16:42:51 by nrea             ###   ########.fr       */
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
	if (shell->p_ar.pipes_nb )
	{
		ft_close_p_ar(shell->p_ar.pipes, shell->p_ar.pipes_nb);
		ft_free_p_ar(shell->p_ar.pipes, shell->p_ar.pipes_nb);
		shell->p_ar.pipes_nb = 0;
	}
	return (-1);
}

static int	ft_err(void)
{
	ft_display_error_msg(NULL, "Internal Error\n");
	return (-1);
}


/*Apply the redirections of the pipes in a exec node
this function is only triggered if pipe_lvl > -1*/
int	ft_apply_pipe_redir(t_node *node, int p_lvl, t_shell *s)
{
	if (s->p_ar.pipes_nb == 0 || !s->p_ar.pipes || !s->p_ar.pipes[0] || !node || !s)
		return (ft_err());
	if (node->side == left)
	{
		if (dup2(s->p_ar.pipes[p_lvl][1], STDOUT_FILENO) == -1)
			return (ft_ret_dup_pipe_err(s));
	}
	else if (node->side == right)
	{
		if (dup2(s->p_ar.pipes[p_lvl][0], STDIN_FILENO) == -1)
			return (ft_ret_dup_pipe_err(s));
		if (p_lvl > 0)
		{
			if (dup2(s->p_ar.pipes[p_lvl - 1][1], STDOUT_FILENO) == -1)
				return (ft_ret_dup_pipe_err(s));
		}
	}
		ft_close_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
		ft_free_p_ar(s->p_ar.pipes, s->p_ar.pipes_nb);
		s->p_ar.pipes_nb = 0;
	return (0);
}
