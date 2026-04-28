/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:47:25 by finorako          #+#    #+#             */
/*   Updated: 2026/04/27 17:50:23 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

void	update_thread_active(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	data->thread_activated += 1;
	pthread_mutex_unlock(&data->lock);
}

int	thread_activated(t_data *data)
{
	int	active;

	active = 0;
	pthread_mutex_lock(&data->lock);
	active = data->thread_activated;
	pthread_mutex_unlock(&data->lock);
	return (active);
}

bool	simulation_done(t_data *data)
{
	bool	done;

	done = false;
	pthread_mutex_lock(&data->lock);
	done = data->burned_out;
	pthread_mutex_unlock(&data->lock);
	return (done);
}
