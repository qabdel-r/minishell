/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmoh-d <abmoh-d@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/12 01:33:17 by abmoh-d          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	ms_strip_cr(char *s)
{
	size_t	len;

	if (s == NULL)
		return ;
	len = ms_strlen(s);
	if (len > 0 && s[len - 1] == '\r')
		s[len - 1] = '\0';
}

int	ms_line_is_delim(const char *line, const char *delim)
{
	if (line == NULL || delim == NULL)
		return (0);
	return (ms_strcmp(line, delim) == 0);
}

void	ms_write_line(int wfd, const char *line)
{
	size_t	i;

	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		write(wfd, &line[i], 1);
		i++;
	}
	write(wfd, "\n", 1);
}
