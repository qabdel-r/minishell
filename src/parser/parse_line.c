/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parse_line(const char *line, t_pipeline **out)
{
	t_token		*tokens;
	int			err;

	if (out == NULL)
		return (1);
	*out = NULL;
	err = 0;
	tokens = ms_lex_line(line, &err);
	if (tokens == NULL)
		return (err);
	if (ms_validate_tokens(tokens, &err) != 0)
	{
		ms_token_clear(&tokens);
		return (err);
	}
	if (ms_parse_tokens(&tokens, out, &err) != 0)
	{
		ms_token_clear(&tokens);
		ms_pipeline_clear(out);
		return (err);
	}
	ms_token_clear(&tokens);
	return (0);
}
