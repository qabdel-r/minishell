/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_more.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ms_strlen(s);
	dup = (char *)malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	while (len > 0)
	{
		len--;
		dup[len] = s[len];
	}
	dup[ms_strlen(s)] = '\0';
	return (dup);
}

int	ms_strcmp(const char *a, const char *b)
{
	size_t	i;

	i = 0;
	while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

int	ms_strncmp(const char *a, const char *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)a[i] - (unsigned char)b[i]);
}

char	*ms_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
