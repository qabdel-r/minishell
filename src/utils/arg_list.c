/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*ms_arg_new(t_part *parts)
{
	t_arg	*node;

	node = (t_arg *)malloc(sizeof(t_arg));
	if (node == NULL)
		return (NULL);
	node->parts = parts;
	node->next = NULL;
	return (node);
}

void	ms_arg_add_back(t_arg **lst, t_arg *new_node)
{
	t_arg	*cur;

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

void	ms_arg_clear(t_arg **lst)
{
	t_arg	*tmp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ms_part_clear(&((*lst)->parts));
		free(*lst);
		*lst = tmp;
	}
}
