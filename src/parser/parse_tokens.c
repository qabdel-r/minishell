/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:40:19 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_init_parse(t_pipeline **p, t_cmd **cmd, int *err);
int	ms_handle_word(t_cmd *cmd, t_token *tok, int *err);
int	ms_handle_pipe(t_pipeline *p, t_cmd **cmd, int *err);
int	ms_handle_redir(t_cmd *cmd, t_token **tokens, int *err);

static int	process_cur(t_pipeline *p, t_cmd **cmd, t_token **tok, int *err)
{
	t_token	*cur;

	cur = *tok;
	if (cur->type == TOK_WORD && ms_handle_word(*cmd, cur, err) != 0)
		return (1);
	if (ms_tok_is_redir(cur->type) == 1)
	{
		if (ms_handle_redir(*cmd, tok, err) != 0)
			return (1);
		return (2);
	}
	if (cur->type == TOK_PIPE && ms_handle_pipe(p, cmd, err) != 0)
		return (1);
	*tok = cur->next;
	free(cur);
	return (0);
}

int	ms_parse_tokens(t_token **tokens, t_pipeline **out, int *err)
{
	t_pipeline	*p;
	t_cmd		*cmd;
	int			ret;

	if (out == NULL || tokens == NULL)
		return (1);
	*out = NULL;
	if (ms_init_parse(&p, &cmd, err) != 0)
		return (1);
	while (*tokens != NULL)
	{
		ret = process_cur(p, &cmd, tokens, err);
		if (ret == 1)
			return (ms_pipeline_clear(&p), 1);
		if (ret == 2)
			continue ;
	}
	*out = p;
	return (0);
}
