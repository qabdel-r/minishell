/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:35:40 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_redirs_only(t_cmd *cmd)
{
	int	save_in;
	int	save_out;

	if (cmd == NULL || cmd->redirs == NULL)
		return (0);
	if (ms_redirs_setup_parent(cmd, &save_in, &save_out) != 0)
		return (1);
	ms_redirs_restore_parent(save_in, save_out);
	return (0);
}

static int	exec_builtin_redir(t_shell *sh, t_cmd *cmd, char **argv)
{
	int	st;
	int	save_in;
	int	save_out;

	if (ms_redirs_setup_parent(cmd, &save_in, &save_out) != 0)
	{
		ms_argv_free(argv);
		return (1);
	}
	st = ms_run_builtin(sh, argv);
	ms_redirs_restore_parent(save_in, save_out);
	return (st);
}

static int	exec_single(t_shell *sh, t_cmd *cmd)
{
	char	**argv;
	int		st;

	if (cmd == NULL)
		return (0);
	if (cmd->args == NULL)
		return (exec_redirs_only(cmd));
	argv = ms_args_to_argv_expanded(sh, cmd->args);
	if (argv == NULL)
		return (1);
	if (ms_is_builtin(argv[0]) == 1)
	{
		if (cmd->redirs != NULL)
			st = exec_builtin_redir(sh, cmd, argv);
		else
			st = ms_run_builtin(sh, argv);
	}
	else
		st = ms_exec_external_cmd(sh, cmd, argv);
	ms_argv_free(argv);
	return (st);
}

int	ms_execute(t_shell *sh, t_pipeline *p)
{
	int	st;

	if (sh == NULL || p == NULL || p->cmds == NULL)
		return (0);
	st = ms_prepare_heredocs(sh, p);
	if (st != 0)
	{
		ms_cleanup_heredocs(p);
		return (st);
	}
	if (p->count == 1)
		st = exec_single(sh, p->cmds);
	else
		st = ms_exec_pipeline(sh, p);
	ms_cleanup_heredocs(p);
	return (st);
}
