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

void	update_thread_active(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	data->thread_activated += 1;
	pthread_mutex_unlock(&data->lock);
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

void	update_coder_burning_state(t_coder *coder, bool value)
{
	pthread_mutex_lock(&coder->data->lock);
	coder->is_burning = value;
	pthread_mutex_unlock(&coder->data->lock);
}

void	update_coder_last_compile_start(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->lock);
	coder->last_compile_time = get_current_time();
	pthread_mutex_unlock(&coder->data->lock);
}

long	coder_compile_start(t_coder *coder)
{
	long	value;

	value = 0;
	pthread_mutex_lock(&coder->data->lock);
	value = coder->last_compile_start;
	pthread_mutex_unlock(&coder->data->lock);
	return (value);
}
