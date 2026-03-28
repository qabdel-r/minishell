/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/17 13:37:39 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>

static void	init_shell(t_shell *sh, char **envp)
{
	sh->env = ms_env_from_envp(envp);
	sh->last_status = 0;
	sh->should_exit = 0;
	sh->exit_status = 0;
	sh->tty_fd = -1;
	sh->pgid = 0;
}

static void	setup_interactive(t_shell *sh)
{
	ms_jobctl_init(sh);
	ms_setup_signals();
}

static void	cleanup_shell(t_shell *sh, int interactive)
{
	rl_clear_history();
	ms_env_clear(&sh->env);
	if (interactive)
		ms_jobctl_cleanup(sh);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;
	int		interactive;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	init_shell(&sh, envp);
	interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	if (interactive)
		setup_interactive(&sh);
	ms_shell_loop(&sh);
	cleanup_shell(&sh, interactive);
	if (sh.should_exit == 1)
		return (sh.exit_status);
	return (sh.last_status);
}
