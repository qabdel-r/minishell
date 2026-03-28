/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	ms_builtin_env(t_shell *sh)
{
	t_env	*e;

	if (sh == NULL)
		return (1);
	e = sh->env;
	while (e != NULL)
	{
		ms_putstr_fd(e->key, 1);
		write(1, "=", 1);
		ms_putendl_fd(e->value, 1);
		e = e->next;
	}
	return (0);
}
