/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	parts_total_len(t_part *p)
{
	size_t	total;

	total = 0;
	while (p != NULL)
	{
		total += ms_strlen(p->text);
		p = p->next;
	}
	return (total);
}

static void	copy_parts(char *dst, t_part *p)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (p != NULL)
	{
		j = 0;
		while (p->text != NULL && p->text[j] != '\0')
		{
			dst[i] = p->text[j];
			i++;
			j++;
		}
		p = p->next;
	}
	dst[i] = '\0';
}

char	*ms_parts_join(t_part *parts)
{
	char	*res;
	size_t	len;

	len = parts_total_len(parts);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	copy_parts(res, parts);
	return (res);
}
