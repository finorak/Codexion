/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:45:06 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 10:53:55 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

bool	insert(t_queue **queue, t_queue *new_queue, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (!queue)
		return (false);
	addback(queue, new_queue);
	pthread_mutex_unlock(mutex);
	return (true);
}

void	pop_first(t_queue **queue)
{
	t_queue	*temp;

	if (!queue || !*queue)
		return ;
	temp = *queue;
	*queue = (*queue)->next;
	free(temp);
}

/*
 * we first of all lock the mutex of the dongle,
 * after that lock the mutex for inserting the new
 * queu into the dongle's que, after that we verify if the
 * coder's burnout is less than the other's coders
 * if yes, we swap them position and only make the
 * first coder in line to take the dngle
 */
void	edf_scheduler(t_coder *coder, t_dongle *dongle)
{
	(void)dongle;
	pthread_mutex_lock(&coder->first_dongle->insert_lock);
	pthread_mutex_unlock(&coder->first_dongle->insert_lock);
	// second dongle
	pthread_mutex_lock(&coder->second_dongle->insert_lock);
	pthread_mutex_unlock(&coder->second_dongle->insert_lock);
	release_dongle(coder);
}
