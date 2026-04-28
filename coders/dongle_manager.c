/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:25:04 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 10:52:37 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

/*
 * lookup if the first coder in first_dongle queue is
 * the the coder, if yes, let them lock else,
 * just wait
 */
void	request_dongle(t_coder *coder)
{
	if (!insert(&coder->first_dongle->queue, newqueue(coder),
			&coder->first_dongle->lock))
		return ;
	pthread_mutex_lock(&coder->first_dongle->lock);
	/*
	while (!is_first(coder->first_dongle->queue, coder))
		pthread_cond_wait(&coder->first_dongle->cond,
			&coder->first_dongle->lock);*/
	print_log(coder, TAKE);
	/*
	while (!is_first(coder->second_dongle->queue, coder))
		pthread_cond_wait(&coder->second_dongle->cond,
			&coder->second_dongle->lock);*/
	// insert(&coder->second_dongle->queue, newqueue(coder),
	//	&coder->second_dongle->lock);
	pthread_mutex_lock(&coder->second_dongle->lock);
	print_log(coder, TAKE);
}

void	release_dongle(t_coder *coder)
{
	busy_sleep(coder->data->time.cooldown);
	// pop_first(&coder->first_dongle->queue);
	// pop_first(&coder->first_dongle->queue);
	pthread_mutex_unlock(&coder->first_dongle->lock);
	pthread_mutex_unlock(&coder->second_dongle->lock);
	// pthread_cond_broadcast(&coder->second_dongle->cond);
	// pthread_cond_broadcast(&coder->first_dongle->cond);
}
