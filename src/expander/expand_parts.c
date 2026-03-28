/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:32:32 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* from expand_core.c */
char			*ms_expand_str(t_shell *sh, const char *s);

static void	copy_str(char *dst, size_t *pos, const char *s)
{
	size_t	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
	{
		dst[*pos] = s[i];
		(*pos)++;
		i++;
	}
}

static size_t	calc_total(t_shell *sh, t_part *parts)
{
	size_t	total;
	char	*tmp;

	total = 0;
	while (parts != NULL)
	{
		if (parts->qtype == Q_SINGLE)
			total += ms_strlen(parts->text);
		else
		{
			tmp = ms_expand_str(sh, parts->text);
			if (tmp == NULL)
				return (0);
			total += ms_strlen(tmp);
			free(tmp);
		}
		parts = parts->next;
	}
	return (total + 1);
}

static int	fill_result(t_shell *sh, t_part *p, char *res, size_t *pos)
{
	char	*tmp;

	while (p != NULL)
	{
		if (p->qtype == Q_SINGLE)
			copy_str(res, pos, p->text);
		else
		{
			tmp = ms_expand_str(sh, p->text);
			if (tmp == NULL)
				return (1);
			copy_str(res, pos, tmp);
			free(tmp);
		}
		p = p->next;
	}
	return (0);
}

char	*ms_expand_parts(t_shell *sh, t_part *parts)
{
	size_t	total;
	size_t	pos;
	char	*res;

	total = calc_total(sh, parts);
	if (total == 0)
		return (NULL);
	res = (char *)malloc(total);
	if (res == NULL)
		return (NULL);
	pos = 0;
	if (fill_result(sh, parts, res, &pos) != 0)
		return (free(res), NULL);
	res[pos] = '\0';
	return (res);
}
