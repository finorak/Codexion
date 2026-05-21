/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:45:06 by finorako          #+#    #+#             */
/*   Updated: 2026/05/20 13:51:22 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
 * Inserting a new queue into the dongle's
 * queue.
 * Locking the mutex, after that we just
 * do simple addback to the queue, after that
 * we unlock the mutex we locked to prevent from
 * deadlock.
 */
bool	insert(t_queue **queue, t_queue *new_queue, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->queue_lock);
	if (!queue)
	{
		pthread_mutex_unlock(&dongle->queue_lock);
		return (false);
	}
	addback(queue, new_queue);
	pthread_mutex_unlock(&dongle->queue_lock);
	return (true);
}

/*
 * Poping the first queue from the dongle's queue
 */
void	pop_first(t_queue **queue, t_dongle *dongle)
{
	t_queue	*temp;

	pthread_mutex_lock(&dongle->queue_lock);
	if (!queue || !*queue)
	{
		pthread_mutex_unlock(&dongle->queue_lock);
		return ;
	}
	temp = *queue;
	*queue = (*queue)->next;
	free(temp);
	pthread_mutex_unlock(&dongle->queue_lock);
}

/*
 * Locking the appropriate queue
 * We then iterat through the queue
 * after that we remove that last item
 * and then unlock the queue to prevent
 * from deadlock
 */
void	pop_last(t_queue **queue, t_dongle *dongle)
{
	t_queue	*temp;
	t_queue	*prev;

	pthread_mutex_lock(&dongle->queue_lock);
	if (!queue || !*queue)
	{
		pthread_mutex_unlock(&dongle->queue_lock);
		return ;
	}
	temp = *queue;
	prev = NULL;
	while (temp->next)
	{
		prev = temp;
		temp = temp->next;
	}
	if (prev)
		prev->next = NULL;
	else
		*queue = NULL;
	free(temp);
	pthread_mutex_unlock(&dongle->queue_lock);
}
