/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:41:12 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int			ms_apply_heredoc(t_redir *r);
int			ms_apply_file_redir(t_redir *r);

static int	apply_one_redir(t_redir *r)
{
	if (r->type == TOK_HEREDOC)
		return (ms_apply_heredoc(r));
	if (r->type == TOK_IN || r->type == TOK_OUT || r->type == TOK_APPEND)
		return (ms_apply_file_redir(r));
	return (0);
}

int	ms_redirs_setup_child(t_cmd *cmd)
{
	t_redir	*r;

	if (cmd == NULL)
		return (0);
	r = cmd->redirs;
	while (r != NULL)
	{
		if (apply_one_redir(r) != 0)
			return (1);
		r = r->next;
	}
	return (0);
}

void	ms_redirs_restore_parent(int save_in, int save_out)
{
	if (save_in >= 0)
	{
		dup2(save_in, 0);
		close(save_in);
	}
	if (save_out >= 0)
	{
		dup2(save_out, 1);
		close(save_out);
	}
}

int	ms_redirs_setup_parent(t_cmd *cmd, int *save_in, int *save_out)
{
	int	in_fd;
	int	out_fd;

	if (save_in == NULL || save_out == NULL)
		return (1);
	in_fd = dup(0);
	out_fd = dup(1);
	*save_in = in_fd;
	*save_out = out_fd;
	if (in_fd < 0 || out_fd < 0)
	{
		ms_redirs_restore_parent(in_fd, out_fd);
		return (1);
	}
	if (ms_redirs_setup_child(cmd) != 0)
	{
		ms_redirs_restore_parent(in_fd, out_fd);
		return (1);
	}
	return (0);
}
