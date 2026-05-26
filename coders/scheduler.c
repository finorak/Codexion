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

#include <unistd.h>
#include "codexion.h"

static bool	ordering_dongle(t_coder *coder)
{
	t_dongle	*a;
	t_dongle	*b;
	t_dongle	*tmp;

	a = coder->first_dongle;
	b = coder->second_dongle;
	if (a > b)
	{
		tmp = a;
		a = b;
		b = tmp;
	}
	pthread_mutex_lock(&a->lock);
	pthread_mutex_lock(&b->lock);
	if (simulation_done(coder->data))
	{
		pthread_mutex_unlock(&b->lock);
		pthread_mutex_unlock(&a->lock);
		return (false);
	}
	return (true);
}

/*
 * Just do a spin till we are the first on both dongle
 */
bool	fifo_scheduler(t_coder *coder,
		t_queue *first_queue, t_queue *second_queue)
{
	if (!first_queue || !second_queue)
		return (false);
	insert(&coder->first_dongle->queue, first_queue, coder->first_dongle);
	insert(&coder->second_dongle->queue, second_queue, coder->second_dongle);
	while (!simulation_done(coder->data))
	{
		if (is_first(coder->first_dongle->queue, coder)
			&& is_first(coder->second_dongle->queue, coder))
			break ;
		usleep(100);
	}
	return (ordering_dongle(coder));
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
	based_insert(&coder->first_dongle->queue, coder, coder->first_dongle);
	based_insert(&coder->second_dongle->queue, coder, coder->second_dongle);
	while (!simulation_done(coder->data))
	{
		if (is_first(coder->first_dongle->queue, coder)
			&& is_first(coder->second_dongle->queue, coder))
			break ;
		usleep(100);
	}
	return (ordering_dongle(coder));
}

bool	scheduler(t_coder *coder, t_queue *first_queue, t_queue *second_queue)
{
	if (coder->data->fifo_scheduler)
		return (fifo_scheduler(coder, first_queue, second_queue));
	return (edf_scheduler(coder, first_queue, second_queue));
}
