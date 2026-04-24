/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:08:31 by finorako          #+#    #+#             */
/*   Updated: 2026/04/24 17:25:07 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	request_dongle(t_coder *coder, int coder_index)
{
	int	right_index;
	int	left_index;

	pthread_mutex_lock(&coder->data->mutex);
	right_index = coder_index - 1;
	left_index = coder_index % coder->data->nb_dongles;
	while (coder->data->dongles[right_index]->in_use)
		pthread_cond_wait(
			&coder->data->dongles[right_index]->cond, &coder->data->mutex
			);
	pthread_mutex_lock(&coder->data->dongles[right_index]->mutex);
	coder->right_dongle = coder->data->dongles[right_index];
	execute_action(coder, TAKE_DONGLE);
	coder->data->dongles[right_index]->in_use = true;
	pthread_mutex_unlock(&coder->data->dongles[right_index]->mutex);
	while (coder->data->dongles[left_index]->in_use)
		pthread_cond_wait(
			&coder->data->dongles[left_index]->cond, &coder->data->mutex
			);
	pthread_mutex_lock(&coder->data->dongles[left_index]->mutex);
	coder->left_dongle = coder->data->dongles[left_index];
	execute_action(coder, TAKE_DONGLE);
	coder->data->dongles[left_index]->in_use = true;
	pthread_mutex_unlock(&coder->data->dongles[left_index]->mutex);
	pthread_mutex_unlock(&coder->data->mutex);
}

void	release_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->mutex);
	if (coder->right_dongle)
	{
		pthread_mutex_lock(&coder->data->dongles[coder->index - 1]->mutex);
		coder->right_dongle = NULL;
		coder->data->dongles[coder->index - 1]->in_use = false;
		pthread_mutex_unlock(&coder->data->dongles[coder->index - 1]->mutex);
		pthread_cond_broadcast(&coder->data->dongles[coder->index - 1]->cond);
	}
	if (coder->left_dongle)
	{
		pthread_mutex_lock(
			&coder->data->dongles[coder->index % coder->data->nb_dongles]->mutex
			);
		coder->left_dongle = NULL;
		coder->data->dongles[coder->index
			% coder->data->nb_dongles]->in_use = false;
		pthread_mutex_unlock(
			&coder->data->dongles[coder->index % coder->data->nb_dongles]->mutex
			);
		pthread_cond_broadcast(&coder->data->dongles[coder->index
			% coder->data->nb_dongles]->cond);
	}
	pthread_mutex_unlock(&coder->data->mutex);
}
