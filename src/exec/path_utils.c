/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:41:12 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	ms_has_slash(const char *s)
{
	if (ms_strchr(s, '/') != NULL)
		return (1);
	return (0);
}

char	*ms_dir_dup(const char *path, size_t start, size_t end)
{
	if (end == start)
		return (ms_strdup("."));
	return (ms_strndup(path + start, end - start));
}

char	*ms_try_path(const char *dir, const char *name, int *perm)
{
	char	*cand;

	cand = ms_strjoin3(dir, "/", name);
	if (cand == NULL)
		return (NULL);
	if (access(cand, X_OK) == 0)
		return (cand);
	if (access(cand, F_OK) == 0 && perm != NULL)
		*perm = 1;
	free(cand);
	return (NULL);
}

char	*ms_check_direct(const char *name, int *st)
{
	if (access(name, F_OK) != 0)
	{
		*st = 127;
		return (NULL);
	}
	if (access(name, X_OK) != 0)
	{
		*st = 126;
		return (NULL);
	}
	return (ms_strdup(name));
}
