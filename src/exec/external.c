/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:41:12 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int			ms_wait_status(int w);
int			ms_handle_resolve_error(const char *cmd, int st);

static void	child_exec(t_shell *sh, char *path, char **argv)
{
	char	**envp;
	int		code;

	envp = ms_env_to_envp(sh->env);
	if (envp == NULL)
		exit(1);
	execve(path, argv, envp);
	code = 126;
	if (errno == ENOENT)
		code = 127;
	if (errno == EACCES)
		code = 126;
	perror(argv[0]);
	ms_envp_free(envp);
	free(path);
	exit(code);
}

int	ms_exec_external(t_shell *sh, char **argv)
{
	char	*path;
	int		st;
	int		w;
	pid_t	pid;

	st = 0;
	path = ms_resolve_cmd(sh, argv[0], &st);
	if (path == NULL)
		return (ms_handle_resolve_error(argv[0], st));
	pid = fork();
	if (pid < 0)
		return (free(path), 1);
	if (pid == 0)
		child_exec(sh, path, argv);
	waitpid(pid, &w, 0);
	free(path);
	return (ms_wait_status(w));
}
