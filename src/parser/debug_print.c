/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void	print_parts(t_part *p)
{
	while (p != NULL)
	{
		ms_putstr_fd("{q=", 1);
		if (p->qtype == Q_NONE)
			ms_putstr_fd("0", 1);
		else if (p->qtype == Q_SINGLE)
			ms_putstr_fd("1", 1);
		else
			ms_putstr_fd("2", 1);
		ms_putstr_fd(",'", 1);
		ms_putstr_fd(p->text, 1);
		ms_putstr_fd("'} ", 1);
		p = p->next;
	}
}

static void	print_args(t_arg *a)
{
	while (a != NULL)
	{
		ms_putstr_fd("ARG: ", 1);
		print_parts(a->parts);
		ms_putendl_fd("", 1);
		a = a->next;
	}
}

static void	print_redirs(t_redir *r)
{
	while (r != NULL)
	{
		ms_putstr_fd("REDIR type=", 1);
		if (r->type == TOK_IN)
			ms_putstr_fd("<", 1);
		else if (r->type == TOK_OUT)
			ms_putstr_fd(">", 1);
		else if (r->type == TOK_APPEND)
			ms_putstr_fd(">>", 1);
		else if (r->type == TOK_HEREDOC)
			ms_putstr_fd("<<", 1);
		ms_putstr_fd(" heredoc_expand=", 1);
		if (r->heredoc_expand == 0)
			ms_putstr_fd("0", 1);
		else
			ms_putstr_fd("1", 1);
		ms_putstr_fd(" target: ", 1);
		print_parts(r->target_parts);
		ms_putendl_fd("", 1);
		r = r->next;
	}
}

void	ms_debug_pipeline(t_pipeline *p)
{
	t_cmd	*c;
	int		i;

	if (p == NULL)
		return ;
	ms_putstr_fd("PIPELINE count=", 1);
	if (p->count < 10)
		write(1, &"0123456789"[p->count], 1);
	ms_putendl_fd("", 1);
	c = p->cmds;
	i = 1;
	while (c != NULL)
	{
		ms_putstr_fd("== CMD ", 1);
		if (i < 10)
			write(1, &"0123456789"[i], 1);
		ms_putendl_fd(" ==", 1);
		print_args(c->args);
		print_redirs(c->redirs);
		c = c->next;
		i++;
	}
}
