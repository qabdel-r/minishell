/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:48:47 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ms_expand_len(t_shell *sh, const char *s);
void	ms_expand_to_buf(t_shell *sh, const char *s, char *dst, size_t *pos);

int	ms_is_var_start(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	ms_is_var_char(char c)
{
	if (ms_is_var_start(c) == 1)
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*ms_env_getn(t_env *env, const char *k, size_t len)
{
	while (env != NULL)
	{
		if (ms_strlen(env->key) == len && ms_strncmp(env->key, k, len) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ms_expand_str(t_shell *sh, const char *s)
{
	char	*res;
	size_t	len;
	size_t	pos;

	if (sh == NULL || s == NULL)
		return (ms_strdup(""));
	len = ms_expand_len(sh, s);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	pos = 0;
	ms_expand_to_buf(sh, s, res, &pos);
	res[pos] = '\0';
	return (res);
}
