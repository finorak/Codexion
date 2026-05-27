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

bool	swap_coder(t_queue **queue, t_coder *coder, t_dongle *dongle)
{
	t_queue	*new_queue;

	pthread_mutex_lock(&dongle->queue_lock);
	if (!queue || !*queue)
	{
		new_queue = newqueue(coder);
		if (!new_queue)
		{
			pthread_mutex_unlock(&dongle->queue_lock);
			return (false);
		}
		addback(queue, newqueue(coder));
		pthread_mutex_unlock(&dongle->queue_lock);
		return (true);
	}
	pthread_mutex_unlock(&dongle->queue_lock);
	return (true);
}

/*
 * Verify if the coder is priority, if yes
 * we swap the value of the first coder in queue
 * and the current coder, else we just add it into
 * the queue
 */
bool	custom_insert(t_queue **queue, t_coder *coder, t_dongle *dongle)
{
	long	deadline;

	pthread_mutex_lock(&dongle->queue_lock);
	if (!queue || !*queue)
	{
		addback(queue, newqueue(coder));
		pthread_mutex_unlock(&dongle->queue_lock);
		return (true);
	}
	deadline = coder_compile_start(coder) + coder->data->time.burnout;
	if (coder_compile_start((*queue)->coder) + coder->data->time.burnout
		< deadline)
	{
		if (!push(queue, newqueue(coder)))
		{
			pthread_mutex_unlock(&dongle->queue_lock);
			return (false);
		}
		pthread_mutex_unlock(&dongle->queue_lock);
		return (true);
	}
	else
		addback(queue, newqueue(coder));
	pthread_mutex_unlock(&dongle->queue_lock);
	return (true);
}

/*
 * Poping the first queue from the dongle's queue
 * so that other coder can use that dongle
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
 * Same as pop_first but with this, we do not lock
 * any mutex in it, because it will just be used
 * by the coder who call it
 */
bool	push(t_queue **queue, t_queue *new_queue)
{
	(void)queue;
	(void)new_queue;
	return (true);
}
