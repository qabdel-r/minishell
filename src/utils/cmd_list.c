/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ms_cmd_new(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (node == NULL)
		return (NULL);
	node->args = NULL;
	node->redirs = NULL;
	node->next = NULL;
	return (node);
}

void	ms_cmd_clear(t_cmd **lst)
{
	t_cmd	*tmp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ms_arg_clear(&((*lst)->args));
		ms_redir_clear(&((*lst)->redirs));
		free(*lst);
		*lst = tmp;
	}
}
