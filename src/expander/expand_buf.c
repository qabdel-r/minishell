/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:32:32 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_is_var_start(char c);
int		ms_is_var_char(char c);
char	*ms_env_getn(t_env *env, const char *k, size_t len);
void	ms_write_int(char *dst, int n, size_t *pos);

static void	copy_val(char *dst, size_t *pos, const char *val)
{
	while (*val != '\0')
	{
		dst[*pos] = *val;
		(*pos)++;
		val++;
	}
}

static void	expand_var(t_shell *sh, const char *s, size_t *i, char *d_p[2])
{
	size_t	j;
	char	*val;
	size_t	*pos;

	pos = (size_t *)d_p[1];
	j = *i + 1;
	while (ms_is_var_char(s[j]) == 1)
		j++;
	val = ms_env_getn(sh->env, s + *i + 1, j - (*i + 1));
	if (val != NULL)
		copy_val(d_p[0], pos, val);
	*i = j;
}

void	ms_expand_to_buf(t_shell *sh, const char *s, char *dst, size_t *pos)
{
	size_t	i;
	char	*d_p[2];

	i = 0;
	d_p[0] = dst;
	d_p[1] = (char *)pos;
	while (s != NULL && s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			ms_write_int(dst, sh->last_status, pos);
			i += 2;
		}
		else if (s[i] == '$' && ms_is_var_start(s[i + 1]) == 1)
			expand_var(sh, s, &i, d_p);
		else
		{
			dst[*pos] = s[i];
			(*pos)++;
			i++;
		}
	}
}
