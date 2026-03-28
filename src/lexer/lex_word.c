/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:29:24 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_qtype	get_qtype(char q)
{
	if (q == '\'')
		return (Q_SINGLE);
	return (Q_DOUBLE);
}

static int	lex_quoted(const char *s, size_t *i, t_part **parts, int *err)
{
	size_t	start;
	char	q;
	char	*txt;

	q = s[*i];
	(*i)++;
	start = *i;
	while (s[*i] != '\0' && s[*i] != q)
		(*i)++;
	if (s[*i] != q)
	{
		if (err != NULL)
			*err = 2;
		return (1);
	}
	txt = ms_strndup(s + start, *i - start);
	if (txt == NULL)
		return (*err = 1, 1);
	ms_part_add_back(parts, ms_part_new(txt, get_qtype(q)));
	(*i)++;
	return (0);
}

static int	lex_plain(const char *s, size_t *i, t_part **parts, int *err)
{
	size_t	start;
	char	*txt;

	start = *i;
	while (s[*i] != '\0' && ms_is_space(s[*i]) == 0 && ms_is_op(s[*i]) == 0
		&& s[*i] != '\'' && s[*i] != '"')
		(*i)++;
	txt = ms_strndup(s + start, *i - start);
	if (txt == NULL)
	{
		if (err != NULL)
			*err = 1;
		return (1);
	}
	ms_part_add_back(parts, ms_part_new(txt, Q_NONE));
	return (0);
}

t_part	*ms_lex_word_parts(const char *s, size_t *i, int *err)
{
	t_part	*parts;

	parts = NULL;
	while (s[*i] != '\0' && ms_is_space(s[*i]) == 0 && ms_is_op(s[*i]) == 0)
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			if (lex_quoted(s, i, &parts, err) != 0)
			{
				ms_part_clear(&parts);
				return (NULL);
			}
		}
		else
		{
			if (lex_plain(s, i, &parts, err) != 0)
			{
				ms_part_clear(&parts);
				return (NULL);
			}
		}
	}
	return (parts);
}
