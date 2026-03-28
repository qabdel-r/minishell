/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:41:12 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int			ms_has_slash(const char *s);
char		*ms_dir_dup(const char *path, size_t start, size_t end);
char		*ms_try_path(const char *dir, const char *name, int *perm);
char		*ms_check_direct(const char *name, int *st);

static char	*search_path_loop(const char *path, const char *name, int *perm)
{
	size_t	i;
	size_t	start;
	char	*dir;
	char	*found;

	i = 0;
	start = 0;
	while (1)
	{
		while (path[i] != '\0' && path[i] != ':')
			i++;
		dir = ms_dir_dup(path, start, i);
		if (dir == NULL)
			return (NULL);
		found = ms_try_path(dir, name, perm);
		free(dir);
		if (found != NULL)
			return (found);
		if (path[i] == '\0')
			break ;
		i++;
		start = i;
	}
	return (NULL);
}

char	*ms_resolve_cmd(t_shell *sh, const char *name, int *st)
{
	char	*path;
	char	*found;
	int		perm;

	if (st != NULL)
		*st = 0;
	if (name == NULL || sh == NULL)
		return (NULL);
	if (ms_has_slash(name) == 1)
		return (ms_check_direct(name, st));
	path = ms_env_get(sh->env, "PATH");
	if (path == NULL)
		return (*st = 127, NULL);
	perm = 0;
	found = search_path_loop(path, name, &perm);
	if (found != NULL)
		return (found);
	if (perm == 1)
		return (*st = 126, NULL);
	return (*st = 127, NULL);
}
