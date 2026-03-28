/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:40:19 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_init_parse(t_pipeline **p, t_cmd **cmd, int *err)
{
	*p = ms_pipeline_new();
	if (*p == NULL)
	{
		if (err != NULL)
			*err = 1;
		return (1);
	}
	*cmd = ms_cmd_new();
	if (*cmd == NULL)
	{
		ms_pipeline_clear(p);
		if (err != NULL)
			*err = 1;
		return (1);
	}
	(*p)->cmds = *cmd;
	(*p)->count = 1;
	return (0);
}

int	ms_handle_word(t_cmd *cmd, t_token *tok, int *err)
{
	t_arg	*arg;

	arg = ms_arg_new(tok->parts);
	if (arg == NULL)
	{
		if (err != NULL)
			*err = 1;
		return (1);
	}
	tok->parts = NULL;
	ms_arg_add_back(&(cmd->args), arg);
	return (0);
}

int	ms_handle_pipe(t_pipeline *p, t_cmd **cmd, int *err)
{
	t_cmd	*new_cmd;

	new_cmd = ms_cmd_new();
	if (new_cmd == NULL)
	{
		if (err != NULL)
			*err = 1;
		return (1);
	}
	(*cmd)->next = new_cmd;
	*cmd = new_cmd;
	p->count += 1;
	return (0);
}

int	ms_handle_redir(t_cmd *cmd, t_token **tokens, int *err)
{
	t_token	*r;
	t_token	*t;
	t_redir	*node;
	int		expand;

	r = *tokens;
	t = r->next;
	expand = 1;
	if (r->type == TOK_HEREDOC && ms_parts_has_quote(t->parts) == 1)
		expand = 0;
	node = ms_redir_new(r->type, t->parts, expand);
	if (node == NULL)
	{
		if (err != NULL)
			*err = 1;
		return (1);
	}
	t->parts = NULL;
	ms_redir_add_back(&(cmd->redirs), node);
	*tokens = t->next;
	free(t);
	free(r);
	return (0);
}
