/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_count(t_env *e)
{
	int	n;

	n = 0;
	while (e != NULL)
	{
		n++;
		e = e->next;
	}
	return (n);
}

static void	free_partial(char **envp, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	**ms_env_to_envp(t_env *env)
{
	char	**envp;
	int		n;
	int		i;

	n = env_count(env);
	envp = (char **)malloc(sizeof(char *) * (n + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		envp[i] = ms_strjoin3(env->key, "=", env->value);
		if (envp[i] == NULL)
		{
			free_partial(envp, i);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	ms_envp_free(char **envp)
{
	int	i;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
