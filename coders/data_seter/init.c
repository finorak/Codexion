/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:33:38 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 13:25:34 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../codexion.h"

void	*test(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&data->mutex);
	printf("Hello you!!\n");
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

void	init_mutex(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		pthread_mutex_init(&data->coders[index].mutex, NULL);
		index++;
	}
}

void	init_thread(t_data *data)
{
	int	index;

	pthread_mutex_init(&data->mutex, NULL);
	index = 0;
	while (index < data->nb_coders)
	{
		pthread_create(&data->coders[index].thread_id,
			NULL, test, data);
		index++;
	}
}

bool	init_coders(t_data *data)
{
	int	index;

	data->coders = (t_coder *)malloc(sizeof(t_coder) * data->nb_coders);
	if (!data->coders)
		return (false);
	index = 0;
	while (index < data->nb_coders)
	{
		data->coders[index] = create_coder(data);
		index++;
	}
	return (true);
}

bool	init(t_data *data)
{
	if (!init_coders(data))
		return (false);
	init_mutex(data);
	init_thread(data);
	return (true);
}
