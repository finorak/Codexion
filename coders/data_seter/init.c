/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:33:38 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 19:12:06 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../codexion.h"

static void	que_utils(t_data *data)
{
	int	index;

	index = 0;
	pthread_mutex_init(&data->mutex, NULL);
	pthread_cond_init(&data->cond, NULL);
	while (index < data->nb_coders)
	{
		pthread_cond_init(&data->coders[index]->cond, NULL);
		pthread_mutex_init(&data->coders[index]->mutex, NULL);
		index++;
	}
}

void	init_thread(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		pthread_create(&data->coders[index]->thread_id,
			NULL, activate_coder, data->coders[index]);
		index++;
	}
}

bool	init_coders(t_data *data)
{
	int	index;

	data->coders = (t_coder **)malloc(sizeof(t_coder *) * data->nb_coders);
	if (!data->coders)
		return (false);
	index = 0;
	while (index < data->nb_coders)
	{
		data->coders[index] = create_coder(data);
		if (!data->coders[index])
		{
			free_memory(data);
			return (false);
		}
		data->coders[index]->index = index % data->nb_coders + 1;
		index++;
	}
	return (true);
}

bool	init(t_data *data)
{
	if (!init_coders(data))
		return (false);
	que_utils(data);
	init_thread(data);
	return (true);
}
