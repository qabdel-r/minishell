/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/17 13:36:45 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

static void	handle_sigint(t_shell *sh, char *line)
{
	if (g_sig == SIGINT)
	{
		sh->last_status = 130;
		g_sig = 0;
		if (line != NULL)
			free(line);
	}
}

static void	process_line(t_shell *sh, char *line)
{
	t_pipeline	*p;
	int			ret;

	if (line[0] != '\0')
		add_history(line);
	p = NULL;
	ret = ms_parse_line(line, &p);
	free(line);
	if (ret != 0)
		sh->last_status = ret;
	if (ret == 0 && p != NULL)
		sh->last_status = ms_execute(sh, p);
	ms_pipeline_clear(&p);
}

void	ms_shell_loop(t_shell *sh)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
		{
			ms_putendl_fd("exit", 1);
			return ;
		}
		if (g_sig == SIGINT)
		{
			handle_sigint(sh, line);
			continue ;
		}
		process_line(sh, line);
		if (sh->should_exit == 1)
			return ;
	}
}
