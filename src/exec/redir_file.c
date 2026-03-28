/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:41:12 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	ms_apply_heredoc(t_redir *r)
{
	if (r->hd_fd < 0)
		return (1);
	dup2(r->hd_fd, 0);
	close(r->hd_fd);
	r->hd_fd = -1;
	return (0);
}

static int	get_file_fd(t_redir *r, const char *path, int *target)
{
	int	fd;

	fd = -1;
	*target = 1;
	if (r->type == TOK_IN)
	{
		fd = open(path, O_RDONLY);
		*target = 0;
	}
	else if (r->type == TOK_OUT)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (r->type == TOK_APPEND)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	ms_apply_file_redir(t_redir *r)
{
	char	*path;
	int		fd;
	int		target;

	path = ms_parts_join(r->target_parts);
	if (path == NULL)
		return (1);
	fd = get_file_fd(r, path, &target);
	if (fd < 0)
	{
		perror(path);
		free(path);
		return (1);
	}
	dup2(fd, target);
	close(fd);
	free(path);
	return (0);
}
