/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/17 13:42:22 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void		ms_strip_cr(char *s);
int			ms_line_is_delim(const char *line, const char *delim);
void		ms_write_line(int wfd, const char *line);
void		ms_hd_setup_signals(void);

static int	handle_sigint(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	return (130);
}

static int	process_line(t_shell *sh, t_redir *r, char *line, int wfd)
{
	char	*out;

	if (r->heredoc_expand == 1)
	{
		out = ms_expand_str(sh, line);
		free(line);
		if (out == NULL)
			return (1);
		ms_write_line(wfd, out);
		free(out);
	}
	else
	{
		ms_write_line(wfd, line);
		free(line);
	}
	return (0);
}

static int	read_loop(t_shell *sh, t_redir *r, char *delim, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_sig == SIGINT)
				return (handle_sigint(fd));
			break ;
		}
		if (g_sig == SIGINT)
			return (free(line), handle_sigint(fd));
		ms_strip_cr(line);
		if (ms_line_is_delim(line, delim) == 1)
		{
			free(line);
			break ;
		}
		if (process_line(sh, r, line, fd[1]) != 0)
			return (close(fd[0]), close(fd[1]), 1);
	}
	return (0);
}

static int	setup_and_read(t_shell *sh, t_redir *r, char *delim, int *fd)
{
	int	saved_stdin;
	int	ret;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin < 0)
		return (close(fd[0]), close(fd[1]), free(delim), 1);
	g_sig = 0;
	ms_hd_setup_signals();
	ret = read_loop(sh, r, delim, fd);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	ms_setup_signals();
	free(delim);
	return (ret);
}

int	ms_run_one_heredoc(t_shell *sh, t_redir *r)
{
	char	*delim;
	int		fd[2];
	int		ret;

	delim = ms_parts_join(r->target_parts);
	if (delim == NULL || pipe(fd) != 0)
		return (free(delim), 1);
	ret = setup_and_read(sh, r, delim, fd);
	if (ret == 130)
	{
		sh->last_status = 130;
		g_sig = 0;
		return (130);
	}
	if (ret != 0)
		return (ret);
	close(fd[1]);
	if (r->hd_fd >= 0)
		close(r->hd_fd);
	r->hd_fd = fd[0];
	return (0);
}
