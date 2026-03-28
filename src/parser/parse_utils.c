/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_tok_is_redir(t_toktype t)
{
	if (t == TOK_IN || t == TOK_OUT || t == TOK_APPEND || t == TOK_HEREDOC)
		return (1);
	return (0);
}

int	ms_parts_has_quote(t_part *p)
{
	while (p != NULL)
	{
		if (p->qtype != Q_NONE)
			return (1);
		p = p->next;
	}
	return (0);
}
