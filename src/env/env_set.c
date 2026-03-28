/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_key(t_env *env, const char *k)
{
	while (env != NULL)
	{
		if (ms_strcmp(env->key, k) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ms_env_set(t_env **env, const char *key, const char *value, int ovr)
{
	t_env	*n;
	char	*v;

	if (env == NULL || key == NULL || value == NULL)
		return (1);
	n = find_key(*env, key);
	if (n != NULL)
	{
		if (ovr == 0)
			return (0);
		v = ms_strdup(value);
		if (v == NULL)
			return (1);
		free(n->value);
		n->value = v;
		return (0);
	}
	if (ms_env__new_and_add(env, ms_strdup(key), ms_strdup(value)) == NULL)
		return (1);
	return (0);
}
