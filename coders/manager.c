/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:45:06 by finorako          #+#    #+#             */
/*   Updated: 2026/05/05 16:32:21 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
 * Adding the coder into the queu
 * locking the insert queu because the queu is
 * a shared resource
 */
bool	insert(t_dongle *dongle, t_queue **queue, t_queue *new_queue)
{
	pthread_mutex_lock(&dongle->insert_lock);
	if (!new_queue)
	{
		pthread_mutex_unlock(&dongle->insert_lock);
		return (false);
	}
	addback(queue, new_queue);
	pthread_mutex_unlock(&dongle->insert_lock);
	return (true);
}

void	pop_first(t_dongle *dongle, t_queue **queue)
{
	t_queue	*temp;

	pthread_mutex_lock(&dongle->insert_lock);
	if (!queue || !*queue)
		return ;
	temp = *queue;
	*queue = temp->next;
	free(temp);
	pthread_mutex_unlock(&dongle->insert_lock);
}

/*
 * we first of all lock the mutex of the dongle,
 * after that lock the mutex for inserting the new
 * queu into the dongle's que, after that we verify if the
 * coder's burnout is less than the other's coders
 * if yes, we swap them position and only make the
 * first coder in line to take the dngle
 */
/*
 *
 *
	(void)dongle;
	pthread_mutex_lock(&coder->first_dongle->insert_lock);
	pthread_mutex_unlock(&coder->first_dongle->insert_lock);
	pthread_mutex_lock(&coder->second_dongle->insert_lock);
	pthread_mutex_unlock(&coder->second_dongle->insert_lock);
	release_dongle(coder);
 *
 */
void	edf_scheduler(t_coder *coder, t_dongle *dongle)
{
	(void)coder;
	(void)dongle;
	return ;
}
