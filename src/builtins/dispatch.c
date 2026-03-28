/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_builtin(const char *name)
{
	if (name == NULL)
		return (0);
	if (ms_strcmp(name, "echo") == 0)
		return (1);
	if (ms_strcmp(name, "pwd") == 0)
		return (1);
	if (ms_strcmp(name, "env") == 0)
		return (1);
	if (ms_strcmp(name, "cd") == 0)
		return (1);
	if (ms_strcmp(name, "export") == 0)
		return (1);
	if (ms_strcmp(name, "unset") == 0)
		return (1);
	if (ms_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

int	ms_run_builtin(t_shell *sh, char **argv)
{
	if (argv == NULL || argv[0] == NULL)
		return (1);
	if (ms_strcmp(argv[0], "echo") == 0)
		return (ms_builtin_echo(argv));
	if (ms_strcmp(argv[0], "pwd") == 0)
		return (ms_builtin_pwd());
	if (ms_strcmp(argv[0], "env") == 0)
		return (ms_builtin_env(sh));
	if (ms_strcmp(argv[0], "cd") == 0)
		return (ms_builtin_cd(sh, argv));
	if (ms_strcmp(argv[0], "export") == 0)
		return (ms_builtin_export(sh, argv));
	if (ms_strcmp(argv[0], "unset") == 0)
		return (ms_builtin_unset(sh, argv));
	if (ms_strcmp(argv[0], "exit") == 0)
		return (ms_builtin_exit(sh, argv));
	return (1);
}
