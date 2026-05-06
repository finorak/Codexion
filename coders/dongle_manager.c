/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:25:04 by finorako          #+#    #+#             */
/*   Updated: 2026/05/05 16:31:40 by finorako         ###   ########.fr       */
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

/*
 * we just hold onto the dongle till the cooldown is reached
 * because if the concurency might be not ok if we don't hold
 * into the dongle first, some other coder might take it
 */
bool	request_dongle(t_coder *coder)
{
	if (simulation_done(coder->data))
		return (false);
	pthread_mutex_lock(&coder->first_dongle->lock);
	if (!wait_dongle_availability(coder->data, coder->first_dongle,
			coder->data->time.cooldown))
	{
		pthread_mutex_unlock(&coder->first_dongle->lock);
		return (false);
	}
	print_log(coder, TAKE);
	pthread_mutex_lock(&coder->second_dongle->lock);
	if (!wait_dongle_availability(coder->data, coder->second_dongle,
			coder->data->time.cooldown))
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
	pthread_mutex_unlock(&coder->second_dongle->lock);
	pthread_mutex_unlock(&coder->first_dongle->lock);
}
