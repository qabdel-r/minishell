/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:32:32 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_env_entry(const char *e, char **k, char **v)
{
	char	*eq;

	eq = ms_strchr(e, '=');
	if (eq == NULL)
	{
		*k = ms_strdup(e);
		*v = ms_strdup("");
	}
	else
	{
		*k = ms_strndup(e, (size_t)(eq - e));
		*v = ms_strdup(eq + 1);
	}
}

static int	add_one(t_env **env, const char *e)
{
	char	*k;
	char	*v;

	parse_env_entry(e, &k, &v);
	if (k == NULL || v == NULL)
	{
		free(k);
		free(v);
		return (1);
	}
	if (ms_env__new_and_add(env, k, v) == NULL)
	{
		free(k);
		free(v);
		return (1);
	}
	return (0);
}

t_env	*ms_env_from_envp(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp != NULL && envp[i] != NULL)
	{
		if (add_one(&env, envp[i]) != 0)
		{
			ms_env_clear(&env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
