/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int	is_n_opt(const char *s)
{
	size_t	i;

	if (s == NULL || s[0] != '-')
		return (0);
	i = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (0);
	return (1);
}

int	ms_builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv != NULL && argv[i] != NULL && is_n_opt(argv[i]) == 1)
	{
		newline = 0;
		i++;
	}
	while (argv != NULL && argv[i] != NULL)
	{
		ms_putstr_fd(argv[i], 1);
		if (argv[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
	return (0);
}
