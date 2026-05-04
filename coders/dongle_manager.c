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

static bool	waiting_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock);
	/*while (!is_first(dongle->queue, coder))
		pthread_cond_wait(&dongle->cond, &dongle->lock);*/
	return (wait_dongle_availability(coder->data, dongle,
			coder->data->time.cooldown));
}

/*
 * we just hold onto the dongle till the cooldown is reached
 * because if the concurency might be not ok if we don't hold
 * into the dongle first, some other coder might take it
 */
bool	request_dongle(t_coder *coder)
{
	if (simulation_done(coder->data))
		return (false);
	if (!insert(coder->first_dongle, &coder->first_dongle->queue,
			newqueue(coder)))
		return (false);
	if (!waiting_dongle(coder, coder->first_dongle))
	{
		pthread_mutex_unlock(&coder->first_dongle->lock);
		return (false);
	}
	print_log(coder, TAKE);
	if (!insert(coder->second_dongle, &coder->second_dongle->queue,
			newqueue(coder)))
		return (false);
	if (!waiting_dongle(coder, coder->second_dongle))
	{
		release_dongle(coder);
		return (false);
	}
	print_log(coder, TAKE);
	update_coder_burning_state(coder, false);
	return (true);
}

/*
 * just releasing the dongle after the compiling is done
 * so that the other coder can take their corespending
 * dongle
 */
void	release_dongle(t_coder *coder)
{
	coder->first_dongle->last_cooldown_time = get_current_time();
	coder->second_dongle->last_cooldown_time = get_current_time();
	pop_first(coder->first_dongle, &coder->first_dongle->queue);
	pop_first(coder->second_dongle, &coder->second_dongle->queue);
	pthread_cond_broadcast(&coder->second_dongle->cond);
	pthread_cond_broadcast(&coder->first_dongle->cond);
	pthread_mutex_unlock(&coder->second_dongle->lock);
	pthread_mutex_unlock(&coder->first_dongle->lock);
}
