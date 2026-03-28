/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobctl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/17 15:44:47 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

void	ms_jobctl_cleanup(t_shell *sh)
{
	if (sh == NULL)
		return ;
	if (sh->tty_fd > STDERR_FILENO)
	{
		close(sh->tty_fd);
		sh->tty_fd = -1;
	}
}

static int	open_tty(void)
{
	int	fd;

	fd = open("/dev/tty", O_RDWR);
	if (fd >= 0)
		return (fd);
	if (isatty(STDIN_FILENO) == 1)
		return (STDIN_FILENO);
	return (-1);
}

static void	disable_echoctl(int fd)
{
	struct termios	t;

	if (fd < 0)
		return ;
	if (tcgetattr(fd, &t) != 0)
		return ;
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(fd, TCSANOW, &t);
}

void	ms_jobctl_set_fg(t_shell *sh, pid_t pgid)
{
	if (sh == NULL || sh->tty_fd < 0)
		return ;
	signal(SIGTTOU, SIG_IGN);
	if (tcsetpgrp(sh->tty_fd, pgid) == -1)
	{
		signal(SIGTTOU, SIG_DFL);
		return ;
	}
	signal(SIGTTOU, SIG_DFL);
}

void	ms_jobctl_init(t_shell *sh)
{
	pid_t	pgid;

	if (sh == NULL)
		return ;
	sh->tty_fd = open_tty();
	disable_echoctl(sh->tty_fd);
	pgid = getpid();
	if (setpgid(0, pgid) != 0)
		sh->pgid = getpgrp();
	else
		sh->pgid = pgid;
	ms_jobctl_set_fg(sh, sh->pgid);
}
