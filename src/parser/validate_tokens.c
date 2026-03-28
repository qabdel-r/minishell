/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:47:07 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_toktype t)
{
	if (t == TOK_IN || t == TOK_OUT || t == TOK_APPEND || t == TOK_HEREDOC)
		return (1);
	return (0);
}

static int	fail_syntax(int *err, const char *tok)
{
	if (err != NULL)
		*err = 2;
	ms_syntax_error(tok);
	return (1);
}

static int	check_pipe(t_token *nxt, int *err)
{
	if (nxt == NULL)
		return (fail_syntax(err, "newline"));
	if (nxt->type == TOK_PIPE)
		return (fail_syntax(err, "|"));
	return (0);
}

static int	check_redir(t_token *nxt, int *err)
{
	if (nxt == NULL)
		return (fail_syntax(err, "newline"));
	if (nxt->type != TOK_WORD)
		return (fail_syntax(err, ms_tok_repr(nxt->type)));
	return (0);
}

int	ms_validate_tokens(t_token *tokens, int *err)
{
	t_token	*cur;

	if (err != NULL)
		*err = 0;
	if (tokens == NULL)
		return (0);
	if (tokens->type == TOK_PIPE)
		return (fail_syntax(err, "|"));
	cur = tokens;
	while (cur != NULL)
	{
		if (cur->type == TOK_PIPE && check_pipe(cur->next, err) != 0)
			return (1);
		if (is_redir(cur->type) && check_redir(cur->next, err) != 0)
			return (1);
		cur = cur->next;
	}
	return (0);
}
