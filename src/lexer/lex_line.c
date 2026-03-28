/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:36:53 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_part				*ms_lex_word_parts(const char *s, size_t *i, int *err);

static t_toktype	get_op_type(const char *s, size_t i)
{
	if (s[i] == '|')
		return (TOK_PIPE);
	if (s[i] == '<' && s[i + 1] == '<')
		return (TOK_HEREDOC);
	if (s[i] == '<')
		return (TOK_IN);
	if (s[i] == '>' && s[i + 1] == '>')
		return (TOK_APPEND);
	return (TOK_OUT);
}

static int	add_op_token(const char *s, size_t *i, t_token **out, int *err)
{
	t_toktype	type;
	t_token		*tok;

	type = get_op_type(s, *i);
	if (type == TOK_HEREDOC || type == TOK_APPEND)
		(*i) += 2;
	else
		(*i) += 1;
	tok = ms_token_new(type, NULL);
	if (tok == NULL)
		return (*err = 1, 1);
	ms_token_add_back(out, tok);
	return (0);
}

static int	add_word_token(const char *s, size_t *i, t_token **out, int *err)
{
	t_part	*parts;
	t_token	*tok;

	parts = ms_lex_word_parts(s, i, err);
	if (parts == NULL)
		return (1);
	tok = ms_token_new(TOK_WORD, parts);
	if (tok == NULL)
	{
		ms_part_clear(&parts);
		return (*err = 1, 1);
	}
	ms_token_add_back(out, tok);
	return (0);
}

static int	process_token(const char *line, size_t *i, t_token **tok, int *err)
{
	if (ms_is_op(line[*i]) == 1)
		return (add_op_token(line, i, tok, err));
	return (add_word_token(line, i, tok, err));
}

t_token	*ms_lex_line(const char *line, int *err)
{
	t_token	*tokens;
	size_t	i;

	tokens = NULL;
	i = 0;
	if (err != NULL)
		*err = 0;
	while (line != NULL && line[i] != '\0')
	{
		while (line[i] != '\0' && ms_is_space(line[i]) == 1)
			i++;
		if (line[i] == '\0')
			break ;
		if (process_token(line, &i, &tokens, err) != 0)
			return (ms_token_clear(&tokens), NULL);
	}
	return (tokens);
}
