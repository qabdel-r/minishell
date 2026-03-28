/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:38:44 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_is_valid_export_key(const char *s)
{
	size_t	i;

	if (s == NULL || s[0] == '\0')
		return (0);
	if (!((s[0] >= 'A' && s[0] <= 'Z') || (s[0] >= 'a' && s[0] <= 'z')
			|| s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] != '\0' && s[i] != '=')
	{
		if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ms_print_export(t_env *e)
{
	while (e != NULL)
	{
		ms_putstr_fd("declare -x ", 1);
		ms_putstr_fd(e->key, 1);
		ms_putstr_fd("=\"", 1);
		ms_putstr_fd(e->value, 1);
		ms_putendl_fd("\"", 1);
		e = e->next;
	}
}

void	ms_print_invalid_export(const char *s)
{
	ms_putstr_fd("minishell: export: `", 2);
	ms_putstr_fd(s, 2);
	ms_putendl_fd("': not a valid identifier", 2);
}

int	ms_set_export_key_val(t_shell *sh, char *k, char *v)
{
	if (ms_env_set(&sh->env, k, v, 1) != 0)
	{
		free(k);
		free(v);
		return (1);
	}
	free(k);
	free(v);
	return (0);
}
