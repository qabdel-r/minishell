/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 17:41:12 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_wait_status(int w)
{
	if (WIFEXITED(w))
		return (WEXITSTATUS(w));
	if (WIFSIGNALED(w))
		return (128 + WTERMSIG(w));
	return (1);
}

int	ms_print_not_found(const char *cmd)
{
	ms_putstr_fd("minishell: ", 2);
	ms_putstr_fd(cmd, 2);
	ms_putendl_fd(": command not found", 2);
	return (127);
}

int	ms_print_perm(const char *cmd)
{
	ms_putstr_fd("minishell: ", 2);
	ms_putstr_fd(cmd, 2);
	ms_putendl_fd(": Permission denied", 2);
	return (126);
}

int	ms_handle_resolve_error(const char *cmd, int st)
{
	if (st == 126)
		return (ms_print_perm(cmd));
	if (st == 127)
		return (ms_print_not_found(cmd));
	return (1);
}
