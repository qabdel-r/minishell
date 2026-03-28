/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:50:45 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int				ms_wait_all(pid_t *pids, int n);
int				ms_run_one_pipe(t_shell *sh, t_cmd *cmd, int fds[5],
					pid_t *d[2]);

static pid_t	*init_pipe(t_pipeline *p, pid_t *pgid, int *prev)
{
	pid_t	*pids;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pids = (pid_t *)malloc(sizeof(pid_t) * p->count);
	*pgid = -1;
	*prev = -1;
	return (pids);
}

static int	run_loop(t_shell *sh, t_pipeline *p, int fds[5], pid_t *d[2])
{
	t_cmd	*cmd;

	cmd = p->cmds;
	fds[2] = -1;
	while (++fds[2] < p->count && cmd != NULL)
	{
		if (ms_run_one_pipe(sh, cmd, fds, d) != 0)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

static int	cleanup_pipe(t_shell *sh, pid_t *pids, int count, pid_t pgid)
{
	int	st;

	(void)pgid;
	st = ms_wait_all(pids, count);
	free(pids);
	ms_jobctl_set_fg(sh, sh->pgid);
	ms_setup_signals();
	return (st);
}

int	ms_exec_pipeline(t_shell *sh, t_pipeline *p)
{
	pid_t	*pids;
	pid_t	pgid;
	int		fds[5];
	pid_t	*d[2];

	pids = init_pipe(p, &pgid, &fds[1]);
	if (pids == NULL)
		return (ms_setup_signals(), 1);
	fds[3] = p->count;
	d[0] = &pgid;
	d[1] = pids;
	if (run_loop(sh, p, fds, d) != 0)
		return (free(pids), ms_setup_signals(), 1);
	if (fds[1] != -1)
		close(fds[1]);
	if (pgid != -1)
		ms_jobctl_set_fg(sh, pgid);
	return (cleanup_pipe(sh, pids, p->count, pgid));
}
