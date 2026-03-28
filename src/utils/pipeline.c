/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qabdel-r <qabdel-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:00:00 by qabdel-r          #+#    #+#             */
/*   Updated: 2026/03/10 12:00:00 by qabdel-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipeline	*ms_pipeline_new(void)
{
	t_pipeline	*p;

	p = (t_pipeline *)malloc(sizeof(t_pipeline));
	if (p == NULL)
		return (NULL);
	p->cmds = NULL;
	p->count = 0;
	return (p);
}

void	ms_pipeline_clear(t_pipeline **p)
{
	if (p == NULL || *p == NULL)
		return ;
	ms_cmd_clear(&((*p)->cmds));
	free(*p);
	*p = NULL;
}
