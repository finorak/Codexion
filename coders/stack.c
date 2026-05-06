/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:17:25 by finorako          #+#    #+#             */
/*   Updated: 2026/05/05 16:32:08 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*newcoder(t_data *data, int index)
{
	t_coder	*coder;

	coder = (t_coder *)malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->data = data;
	coder->index = index % data->counter.nb_coders + 1;
	coder->compile_count = 0;
	coder->last_compile_time = data->time.start_time;
	coder->is_burning = true;
	return (coder);
}

t_dongle	*newdongle(int index)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->index = index;
	dongle->queue = NULL;
	dongle->last_cooldown_time = 0;
	return (dongle);
}

t_queue	*newqueue(t_coder *coder)
{
	t_queue		*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->coder = coder;
	queue->next = NULL;
	queue->id = coder->index & coder->data->counter.nb_coders;
	return (queue);
}

void	addback(t_queue **queue, t_queue *new_queue)
{
	t_queue	*last;

	if (!queue)
		return ;
	if (!*queue)
	{
		*queue = new_queue;
		return ;
	}
	last = *queue;
	while (last->next)
		last = last->next;
	last->next = new_queue;
}
