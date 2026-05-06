/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:47:25 by finorako          #+#    #+#             */
/*   Updated: 2026/05/05 16:32:38 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	update_thread_active(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	data->counter.thread_activated += 1;
	pthread_mutex_unlock(&data->lock);
}

/*
int	thread_activated(t_data *data)
{
	int	active;

	active = 0;
	pthread_mutex_lock(&data->lock);
	active = data->thread_activated;
	pthread_mutex_unlock(&data->lock);
	return (active);
}*/

bool	simulation_done(t_data *data)
{
	bool	done;

	done = false;
	pthread_mutex_lock(&data->lock);
	done = data->burned_out;
	pthread_mutex_unlock(&data->lock);
	return (done);
}

void	update_coder_burning_state(t_coder *coder, bool value)
{
	pthread_mutex_lock(&coder->data->lock);
	coder->is_burning = value;
	pthread_mutex_unlock(&coder->data->lock);
}
