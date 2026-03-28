/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:35:40 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		ms_run_one_heredoc(t_shell *sh, t_redir *r);

int	ms_prepare_heredocs(t_shell *sh, t_pipeline *p)
{
	t_cmd	*c;
	t_redir	*r;
	int		st;

	if (p == NULL)
		return (0);
	c = p->cmds;
	while (c != NULL)
	{
		r = c->redirs;
		while (r != NULL)
		{
			if (r->type == TOK_HEREDOC)
			{
				st = ms_run_one_heredoc(sh, r);
				ms_setup_signals();
				if (st != 0)
					return (st);
			}
			r = r->next;
		}
		c = c->next;
	}
	return (0);
}

void	ms_cleanup_heredocs(t_pipeline *p)
{
	t_cmd	*c;
	t_redir	*r;

	if (p == NULL)
		return ;
	c = p->cmds;
	while (c != NULL)
	{
		r = c->redirs;
		while (r != NULL)
		{
			if (r->type == TOK_HEREDOC && r->hd_fd >= 0)
			{
				close(r->hd_fd);
				r->hd_fd = -1;
			}
			r = r->next;
		}
		c = c->next;
	}
}
