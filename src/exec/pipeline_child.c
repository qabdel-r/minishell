/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:42:11 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ms_reset_child_signals(void);
void	ms_setup_child_fds(int in_fd, int out_fd);

void	ms_child_run(t_shell *sh, t_cmd *cmd, int in_fd, int out_fd)
{
	char	**argv;
	int		st;

	ms_reset_child_signals();
	ms_setup_child_fds(in_fd, out_fd);
	if (ms_redirs_setup_child(cmd) != 0)
		exit(1);
	if (cmd == NULL || cmd->args == NULL)
		exit(0);
	argv = ms_args_to_argv_expanded(sh, cmd->args);
	if (argv == NULL)
		exit(1);
	if (ms_is_builtin(argv[0]) == 1)
	{
		st = ms_run_builtin(sh, argv);
		ms_argv_free(argv);
		exit(st);
	}
	ms_exec_external_in_child(sh, argv);
	exit(1);
}
