/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_part	*ms_part_new(char *text, t_qtype qtype)
{
	t_part	*node;

	node = (t_part *)malloc(sizeof(t_part));
	if (node == NULL)
		return (NULL);
	node->text = text;
	node->qtype = qtype;
	node->next = NULL;
	return (node);
}

void	ms_part_add_back(t_part **lst, t_part *new_node)
{
	t_part	*cur;

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

void	ms_part_clear(t_part **lst)
{
	t_part	*tmp;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free((*lst)->text);
		free(*lst);
		*lst = tmp;
	}
}
