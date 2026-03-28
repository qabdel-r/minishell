/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

static void	reset_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static int	wait_status(int w)
{
	if (WIFEXITED(w))
		return (WEXITSTATUS(w));
	if (WIFSIGNALED(w))
		return (128 + WTERMSIG(w));
	return (1);
}

int	ms_exec_external_cmd(t_shell *sh, t_cmd *cmd, char **argv)
{
	pid_t	pid;
	int		w;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (ms_setup_signals(), 1);
	if (pid == 0)
	{
		setpgid(0, 0);
		reset_child_signals();
		if (ms_redirs_setup_child(cmd) != 0)
			exit(1);
		ms_exec_external_in_child(sh, argv);
		exit(1);
	}
	setpgid(pid, pid);
	ms_jobctl_set_fg(sh, pid);
	waitpid(pid, &w, 0);
	ms_jobctl_set_fg(sh, sh->pgid);
	ms_setup_signals();
	return (wait_status(w));
}
