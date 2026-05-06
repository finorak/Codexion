/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:53:57 by finorako          #+#    #+#             */
/*   Updated: 2026/05/05 16:32:34 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	print_data(t_data *data)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("nb_coders: %d\n", data->counter.nb_coders);
	printf("nb_dongles: %d\n", data->counter.nb_dongles);
	printf("burnout_time: %ld\n", data->time.burnout);
	printf("compile_time; %ld\n", data->time.compile);
	printf("debug_time: %ld\n", data->time.debug);
	printf("refactor_time: %ld\n", data->time.refactor);
	printf("compile_required: %d\n", data->counter.compile_required);
	printf("dongle_cooldown: %ld\n", data->time.cooldown);
	printf("scheduler: %s\n", data->scheduler);
	pthread_mutex_unlock(&data->print_mutex);
}

void	print_waitlst(t_queue *queue)
{
	pthread_mutex_t	*mutex;

	if (!queue)
		return ;
	mutex = &queue->coder->data->print_mutex;
	pthread_mutex_lock(mutex);
	printf("\ninside queue %d\n", queue->id);
	while (queue)
	{
		printf("coder: %d\n", queue->coder->index);
		queue = queue->next;
	}
	printf("\n");
	pthread_mutex_unlock(mutex);
}

void	print_coder_state(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->print_mutex);
	printf("coder: %d\n", coder->index);
	printf("\t%d\n", coder->is_burning);
	pthread_mutex_unlock(&coder->data->print_mutex);
}
