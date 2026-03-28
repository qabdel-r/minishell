/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_new(char *k, char *v)
{
	t_env	*n;

	n = (t_env *)malloc(sizeof(t_env));
	if (n == NULL)
		return (NULL);
	n->key = k;
	n->value = v;
	n->next = NULL;
	return (n);
}

static void	env_add_back(t_env **lst, t_env *n)
{
	t_env	*cur;

	if (lst == NULL || n == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = n;
		return ;
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = n;
}

void	ms_env_clear(t_env **env)
{
	t_env	*tmp;

	if (env == NULL)
		return ;
	while (*env != NULL)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}

/* used by env_build.c */
t_env	*ms_env__new_and_add(t_env **env, char *k, char *v)
{
	t_env	*n;

	n = env_new(k, v);
	if (n == NULL)
		return (NULL);
	env_add_back(env, n);
	return (n);
}
