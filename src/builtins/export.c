/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:38:44 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int			ms_is_valid_export_key(const char *s);
void		ms_print_export(t_env *e);
void		ms_print_invalid_export(const char *s);
int			ms_set_export_key_val(t_shell *sh, char *k, char *v);

static int	do_one(t_shell *sh, const char *s)
{
	char	*eq;
	char	*k;
	char	*v;

	if (ms_is_valid_export_key(s) == 0)
		return (ms_print_invalid_export(s), 1);
	eq = ms_strchr(s, '=');
	if (eq == NULL)
		return (ms_env_set(&sh->env, s, "", 0));
	k = ms_strndup(s, (size_t)(eq - s));
	v = ms_strdup(eq + 1);
	if (k == NULL || v == NULL)
	{
		free(k);
		free(v);
		return (1);
	}
	return (ms_set_export_key_val(sh, k, v));
}

int	ms_builtin_export(t_shell *sh, char **argv)
{
	int	i;
	int	st;

	if (sh == NULL)
		return (1);
	if (argv[1] == NULL)
	{
		ms_print_export(sh->env);
		return (0);
	}
	i = 1;
	st = 0;
	while (argv[i] != NULL)
	{
		if (do_one(sh, argv[i]) != 0)
			st = 1;
		i++;
	}
	return (st);
}
