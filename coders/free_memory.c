/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:27:56 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 09:00:23 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	release(t_data *data)
{
	int	index;

	if (!data)
		return ;
	index = 0;
	while (index < data->nb_coders)
	{
		pthread_mutex_destroy(&data->dongles[index]->lock);
		pthread_cond_destroy(&data->dongles[index]->cond);
		index++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->lock);
	pthread_cond_destroy(&data->cond);
}

void	free_queue(t_queue	*queue)
{
	t_queue	*temp;

	if (!queue)
		return ;
	while (queue)
	{
		temp = queue->next;
		free(queue);
		queue = temp;
	}
}

void	free_dongles(t_dongle **dongles, int size)
{
	int	index;

	if (!dongles)
		return ;
	index = 0;
	while (index < size)
	{
		free(dongles[index]);
		index++;
	}
	free(dongles);
}

void	free_coders(t_coder **coders, int size)
{
	int	index;

	if (!coders)
		return ;
	index = 0;
	while (index < size)
	{
		free(coders[index]);
		index++;
	}
	free(coders);
}

void	cleanup(t_data *data)
{
	if (!data)
		return ;
	release(data);
	free_dongles(data->dongles, data->nb_dongles);
	free_coders(data->coders, data->nb_coders);
}
