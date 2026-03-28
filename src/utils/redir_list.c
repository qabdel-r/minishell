/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

t_redir	*ms_redir_new(t_toktype type, t_part *target, int h_expand)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->target_parts = target;
	node->heredoc_expand = h_expand;
	node->hd_fd = -1;
	node->next = NULL;
	return (node);
}

void	ms_redir_add_back(t_redir **lst, t_redir *new_node)
{
	t_redir	*cur;

	if (lst == NULL || new_node == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	cur = *lst;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new_node;
}

void	ms_redir_clear(t_redir **lst)
{
	t_redir	*tmp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		if ((*lst)->hd_fd >= 0)
			close((*lst)->hd_fd);
		ms_part_clear(&((*lst)->target_parts));
		free(*lst);
		*lst = tmp;
	}
}
