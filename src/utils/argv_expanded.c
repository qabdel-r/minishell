/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_expanded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_count(t_arg *a)
{
	int	n;

	n = 0;
	while (a != NULL)
	{
		n++;
		a = a->next;
	}
	return (n);
}

static void	free_partial(char **argv, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

char	**ms_args_to_argv_expanded(t_shell *sh, t_arg *args)
{
	char	**argv;
	int		n;
	int		i;

	n = arg_count(args);
	argv = (char **)malloc(sizeof(char *) * (n + 1));
	if (argv == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		argv[i] = ms_expand_parts(sh, args->parts);
		if (argv[i] == NULL)
		{
			free_partial(argv, i);
			return (NULL);
		}
		args = args->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
