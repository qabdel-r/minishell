/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/17 13:36:45 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>

static int	is_num(const char *s)
{
	int	i;

	if (s == NULL || s[0] == '\0')
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	to_status(const char *s)
{
	long	n;
	int		sign;
	int		i;

	n = 0;
	sign = 1;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	n = n * sign;
	n = n % 256;
	if (n < 0)
		n += 256;
	return ((int)n);
}

static void	set_exit(t_shell *sh, int code)
{
	if (sh != NULL)
	{
		sh->should_exit = 1;
		sh->exit_status = code;
	}
}

int	ms_builtin_exit(t_shell *sh, char **argv)
{
	int	st;

	ms_putendl_fd("exit", 1);
	if (argv[1] == NULL)
	{
		set_exit(sh, sh->last_status);
		return (sh->last_status);
	}
	if (is_num(argv[1]) == 0)
	{
		ms_putstr_fd("minishell: exit: ", 2);
		ms_putstr_fd(argv[1], 2);
		ms_putendl_fd(": numeric argument required", 2);
		set_exit(sh, 2);
		return (2);
	}
	if (argv[2] != NULL)
	{
		ms_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	st = to_status(argv[1]);
	set_exit(sh, st);
	return (st);
}
