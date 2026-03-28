/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:42:11 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void	ms_reset_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	ms_status_from_wait(int w)
{
	if (WIFEXITED(w))
		return (WEXITSTATUS(w));
	if (WIFSIGNALED(w))
		return (128 + WTERMSIG(w));
	return (1);
}

int	ms_wait_all(pid_t *pids, int n)
{
	int	i;
	int	w;
	int	last;

	i = 0;
	last = 0;
	while (i < n)
	{
		waitpid(pids[i], &w, 0);
		if (i == n - 1)
			last = ms_status_from_wait(w);
		i++;
	}
	return (last);
}

void	ms_setup_child_fds(int in_fd, int out_fd)
{
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (out_fd != 1)
	{
		dup2(out_fd, 1);
		close(out_fd);
	}
}
