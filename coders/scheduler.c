/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:45:26 by finorako          #+#    #+#             */
/*   Updated: 2026/05/20 13:50:58 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

static bool	ordering_dongle(t_coder *coder)
{
	if (coder->first_dongle->index < coder->second_dongle->index)
	{
		pthread_mutex_lock(&coder->first_dongle->lock);
		pthread_mutex_lock(&coder->second_dongle->lock);
	}
	else
	{
		pthread_mutex_lock(&coder->second_dongle->lock);
		pthread_mutex_lock(&coder->first_dongle->lock);
	}
	if (simulation_done(coder->data))
	{
		pthread_mutex_unlock(&coder->first_dongle->lock);
		pthread_mutex_unlock(&coder->second_dongle->lock);
		return (false);
	}
	return (true);
}

static bool	fifo_scheduler(t_coder *coder,
		t_queue *first_queue, t_queue *second_queue)
{
	if (!first_queue || !second_queue)
		return (false);
	insert(&coder->first_dongle->queue, first_queue, coder->first_dongle);
	insert(&coder->second_dongle->queue, second_queue, coder->second_dongle);
	if (!ordering_dongle(coder))
		return (false);
	while (!simulation_done(coder->data))
	{
		if (is_first(coder->first_dongle->queue, coder, coder->first_dongle)
			&& is_first(coder->second_dongle->queue, coder,
				coder->second_dongle))
			return (true);
		if (!is_first(coder->first_dongle->queue, coder, coder->first_dongle))
			pthread_cond_wait(&coder->first_dongle->cond,
				&coder->first_dongle->insert_lock);
		if (!is_first(coder->second_dongle->queue, coder, coder->second_dongle))
			pthread_cond_wait(&coder->second_dongle->cond,
				&coder->second_dongle->insert_lock);
	}
	pthread_mutex_unlock(&coder->first_dongle->insert_lock);
	pthread_mutex_unlock(&coder->second_dongle->insert_lock);
	return (false);
}

/*
 * we first of all lock the mutex of the dongle,
 * after that lock the mutex for inserting the new
 * queu into the dongle's que, after that we verify if the
 * coder's burnout is less than the other's coders
 * if yes, we swap them position and only make the
 * first coder in line to take the dngle
 */
static bool	edf_scheduler(t_coder *coder,
		t_queue *first_queue, t_queue *second_queue)
{
	if (!first_queue | !second_queue)
		return (false);
	(void)coder;
	return (true);
}

bool	scheduler(t_coder *coder, t_queue *first_queue, t_queue *second_queue)
{
	if (coder->data->fifo_scheduler)
		return (fifo_scheduler(coder, first_queue, second_queue));
	return (edf_scheduler(coder, first_queue, second_queue));
}
