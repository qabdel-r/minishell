/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:45:45 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <unistd.h>

void		ms_child_run(t_shell *sh, t_cmd *cmd, int in_fd, int out_fd);

static void	do_child(t_shell *sh, t_cmd *cmd, int fds[4], pid_t pgid)
{
	if (pgid == -1)
		setpgid(0, 0);
	else
		setpgid(0, pgid);
	if (fds[2] < fds[3] - 1)
		close(fds[0]);
	ms_child_run(sh, cmd, fds[1], fds[4]);
}

static void	parent_post(pid_t pid, pid_t *pgid, pid_t *pids, int idx)
{
	if (*pgid == -1)
		*pgid = pid;
	setpgid(pid, *pgid);
	pids[idx] = pid;
}

static void	update_fds(int fds[5], int fd_tmp[2], int count)
{
	if (fds[1] != -1)
		close(fds[1]);
	if (fds[2] < count - 1)
	{
		close(fds[4]);
		fds[1] = fd_tmp[0];
	}
	else
		fds[1] = -1;
}

int	ms_run_one_pipe(t_shell *sh, t_cmd *cmd, int fds[5], pid_t *d[2])
{
	int		fd_tmp[2];
	pid_t	pid;

	if (fds[2] < fds[3] - 1 && pipe(fd_tmp) != 0)
		return (1);
	fds[0] = fd_tmp[0];
	fds[4] = 1;
	if (fds[2] < fds[3] - 1)
		fds[4] = fd_tmp[1];
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		do_child(sh, cmd, fds, *d[0]);
	parent_post(pid, d[0], d[1], fds[2]);
	update_fds(fds, fd_tmp, fds[3]);
	return (0);
}
