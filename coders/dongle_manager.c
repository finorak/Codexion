/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:25:04 by finorako          #+#    #+#             */
/*   Updated: 2026/05/04 14:12:55 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "codexion.h"

/*
 * here we just wait till the cooldown is reached
*/
static bool	wait_dongle_availability(t_data *data, t_dongle *dongle,
		long cooldown_ms)
{
	long	elapsed;
	long	remaining;

	while (!simulation_done(data))
	{
		elapsed = get_current_time() - dongle->last_cooldown_time;
		if (elapsed >= cooldown_ms)
			return (true);
		remaining = cooldown_ms - elapsed;
		if (remaining < 100)
			usleep(500);
		else
			usleep(cooldown_ms / 2);
	}
	return (false);
}

static bool	dongle_aquired(t_dongle **first_dongle,
		t_dongle **second_dongle, t_coder *coder)
{
	pthread_mutex_lock(&(*first_dongle)->lock);
	while ((*first_dongle)->queue->coder != coder
		&& !simulation_done(coder->data))
		pthread_cond_wait(&(*first_dongle)->cond, &(*first_dongle)->lock);
	pthread_mutex_unlock(&(*first_dongle)->lock);
	if (simulation_done(coder->data))
		return (false);
	pthread_mutex_lock(&(*second_dongle)->lock);
	while ((*second_dongle)->queue->coder != coder
		&& !simulation_done(coder->data))
		pthread_cond_wait(&(*second_dongle)->cond, &(*second_dongle)->lock);
	pthread_mutex_unlock(&(*second_dongle)->lock);
	if (simulation_done(coder->data))
		return (false);
	return (true);
}

static bool	insert_and_wait(t_dongle **first_dongle,
		t_dongle **second_dongle, t_coder *coder)
{
	if (!insert(*first_dongle, &(*first_dongle)->queue, newqueue(coder)))
		return (false);
	if (!insert(*second_dongle, &(*second_dongle)->queue, newqueue(coder)))
		return (false);
	if (!dongle_aquired(first_dongle, second_dongle, coder))
		return (false);
	if (!wait_dongle_availability(coder->data,
			*first_dongle, coder->data->time.cooldown))
		return (false);
	if (!wait_dongle_availability(coder->data,
			*second_dongle, coder->data->time.cooldown))
		return (false);
	return (true);
}

/*
 * we acquire both locks in order of dongle index to prevent deadlock
 * FIFO requires us to acquire both before waiting to avoid circular dependencies
 */
bool	request_dongle(t_coder *coder)
{
	t_dongle	*first_dongle;
	t_dongle	*second_dongle;
	t_dongle	*temp;

	if (simulation_done(coder->data))
		return (false);
	first_dongle = coder->first_dongle;
	second_dongle = coder->second_dongle;
	if (first_dongle->index > second_dongle->index)
	{
		temp = first_dongle;
		first_dongle = second_dongle;
		second_dongle = temp;
	}
	if (!insert_and_wait(&first_dongle, &second_dongle, coder))
		return (false);
	coder->first_dongle = first_dongle;
	coder->second_dongle = second_dongle;
	print_log(coder, TAKE);
	print_log(coder, TAKE);
	update_coder_burning_state(coder, false);
	return (true);
}

/*
 * just releasing the dongle after the compiling is done
 * release in reverse order of acquisition
 */
void	release_dongle(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	t_dongle	*temp;

	first = coder->first_dongle;
	second = coder->second_dongle;
	if (first->index > second->index)
	{
		temp = first;
		first = second;
		second = temp;
	}
	first->last_cooldown_time = get_current_time();
	second->last_cooldown_time = get_current_time();
	pthread_mutex_lock(&second->lock);
	pop_first(second, &second->queue);
	pthread_cond_broadcast(&second->cond);
	pthread_mutex_unlock(&second->lock);
	pthread_mutex_lock(&first->lock);
	pop_first(first, &first->queue);
	pthread_cond_broadcast(&first->cond);
	pthread_mutex_unlock(&first->lock);
}
