/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*ms_tok_repr(t_toktype type)
{
	if (type == TOK_PIPE)
		return ("|");
	if (type == TOK_IN)
		return ("<");
	if (type == TOK_OUT)
		return (">");
	if (type == TOK_APPEND)
		return (">>");
	if (type == TOK_HEREDOC)
		return ("<<");
	return ("word");
}

void	ms_syntax_error(const char *tok)
{
	ms_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ms_putstr_fd(tok, 2);
	ms_putendl_fd("'", 2);
}
