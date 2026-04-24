/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:00:14 by finorako          #+#    #+#             */
/*   Updated: 2026/04/24 13:48:58 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../codexion.h"

static void	release_coders(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		if (data->coders[index])
		{
			pthread_mutex_destroy(&data->coders[index]->mutex);
			pthread_cond_destroy(&data->coders[index]->cond);
			free(data->coders[index]);
		}
		index++;
	}
}

static void	release_dongles(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		if (data->dongles[index])
		{
			free(data->dongles[index]->name);
			free(data->dongles[index]);
		}
		index++;
	}
}

void	free_memory(t_data *data)
{
	if (!data)
		return ;
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->action_mutex);
	pthread_cond_destroy(&data->cond);
	if (data->coders)
		release_coders(data);
	if (data->dongles)
		release_dongles(data);
	free(data->coders);
	free(data->dongles);
}
