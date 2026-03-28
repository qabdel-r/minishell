/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:32:32 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ms_is_var_start(char c);
int				ms_is_var_char(char c);
char			*ms_env_getn(t_env *env, const char *k, size_t len);

static size_t	int_len(int n)
{
	size_t	len;

	len = 1;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	ms_write_int(char *dst, int n, size_t *pos)
{
	char	tmp[12];
	size_t	i;

	i = 0;
	if (n == 0)
		tmp[i++] = '0';
	while (n > 0)
	{
		tmp[i++] = (char)('0' + (n % 10));
		n = n / 10;
	}
	while (i > 0)
	{
		i--;
		dst[*pos] = tmp[i];
		(*pos)++;
	}
}

static size_t	expand_len_var(t_shell *sh, const char *s, size_t *i)
{
	size_t	j;
	char	*val;

	j = *i + 1;
	while (ms_is_var_char(s[j]) == 1)
		j++;
	val = ms_env_getn(sh->env, s + *i + 1, j - (*i + 1));
	*i = j;
	if (val != NULL)
		return (ms_strlen(val));
	return (0);
}

size_t	ms_expand_len(t_shell *sh, const char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s != NULL && s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			len += int_len(sh->last_status);
			i += 2;
		}
		else if (s[i] == '$' && ms_is_var_start(s[i + 1]) == 1)
			len += expand_len_var(sh, s, &i);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}
