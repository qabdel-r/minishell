/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/17 13:36:45 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig = 0;

static void	sigint_prompt(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_heredoc(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

static void	set_action(int sig, void (*h)(int), int flags)
{
	struct sigaction	sa;

	sa.sa_handler = h;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = flags;
	sigaction(sig, &sa, NULL);
}

void	ms_setup_signals(void)
{
	set_action(SIGINT, sigint_prompt, 0);
	set_action(SIGQUIT, SIG_IGN, 0);
}

void	ms_hd_setup_signals(void)
{
	set_action(SIGINT, sigint_heredoc, 0);
	set_action(SIGQUIT, SIG_IGN, 0);
}
