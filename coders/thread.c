/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:46:08 by finorako          #+#    #+#             */
/*   Updated: 2026/05/04 12:56:30 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_thread_utils(t_data *data)
{
	int	index;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->lock, NULL);
	pthread_cond_init(&data->cond, NULL);
	index = 0;
	while (index < data->nb_dongles)
	{
		pthread_mutex_init(&data->dongles[index]->insert_lock, NULL);
		pthread_mutex_init(&data->dongles[index]->lock, NULL);
		pthread_cond_init(&data->dongles[index]->cond, NULL);
		index++;
	}
}

//release(data);
void	init_thread(t_data *data)
{
	int	index;

	init_thread_utils(data);
	pthread_create(&data->thread_id, NULL, monitoring_thread, data);
	index = 0;
	while (index < data->nb_coders)
	{
		pthread_create(&data->coders[index]->thread_id,
			NULL, coder_thread, data->coders[index]);
		index++;
	}
}

void	join_thread(t_data *data)
{
	int	index;

	pthread_join(data->thread_id, NULL);
	index = 0;
	while (index < data->nb_coders)
	{
		pthread_join(data->coders[index]->thread_id, NULL);
		index++;
	}
}
