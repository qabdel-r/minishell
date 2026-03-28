/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	copy_at(char *dst, const char *s, size_t i)
{
	size_t	j;

	j = 0;
	while (s != NULL && s[j] != '\0')
	{
		dst[i] = s[j];
		i++;
		j++;
	}
	return (i);
}

char	*ms_strjoin(const char *a, const char *b)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ms_strlen(a) + ms_strlen(b);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	i = copy_at(res, a, i);
	i = copy_at(res, b, i);
	res[i] = '\0';
	return (res);
}

char	*ms_strjoin3(const char *a, const char *b, const char *c)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ms_strlen(a) + ms_strlen(b) + ms_strlen(c);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	i = copy_at(res, a, i);
	i = copy_at(res, b, i);
	i = copy_at(res, c, i);
	res[i] = '\0';
	return (res);
}
