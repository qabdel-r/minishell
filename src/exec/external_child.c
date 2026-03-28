/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:33:54 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

static void	exit_not_found(const char *cmd)
{
	ms_putstr_fd("minishell: ", 2);
	ms_putstr_fd(cmd, 2);
	ms_putendl_fd(": command not found", 2);
	exit(127);
}

static void	exit_perm(const char *cmd)
{
	ms_putstr_fd("minishell: ", 2);
	ms_putstr_fd(cmd, 2);
	ms_putendl_fd(": Permission denied", 2);
	exit(126);
}

static void	handle_resolve_err(const char *cmd, int st)
{
	if (st == 126)
		exit_perm(cmd);
	if (st == 127)
		exit_not_found(cmd);
	exit(1);
}

static void	do_execve(char *path, char **argv, char **envp)
{
	execve(path, argv, envp);
	perror(argv[0]);
	ms_envp_free(envp);
	free(path);
	if (errno == EACCES)
		exit(126);
	if (errno == ENOENT)
		exit(127);
	exit(1);
}

void	ms_exec_external_in_child(t_shell *sh, char **argv)
{
	char	*path;
	char	**envp;
	int		st;

	st = 0;
	path = ms_resolve_cmd(sh, argv[0], &st);
	if (path == NULL)
		handle_resolve_err(argv[0], st);
	envp = ms_env_to_envp(sh->env);
	if (envp == NULL)
		exit(1);
	do_execve(path, argv, envp);
}
