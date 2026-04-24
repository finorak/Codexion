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
	while (coder->data->dongles[right_index]->in_use
		|| coder->data->dongles[left_index]->in_use)
		pthread_cond_wait(&coder->data->cond, &coder->data->mutex);
	coder->right_dongle = coder->data->dongles[right_index];
	coder->data->dongles[right_index]->in_use = true;
	execute_action(coder, TAKE_DONGLE);
	coder->left_dongle = coder->data->dongles[left_index];
	coder->data->dongles[left_index]->in_use = true;
	execute_action(coder, TAKE_DONGLE);
	pthread_mutex_unlock(&coder->data->mutex);
}

void	release_dongle(t_coder *coder)
{
	int	right_index;
	int	left_index;

	pthread_mutex_lock(&coder->data->mutex);
	right_index = coder->index - 1;
	left_index = coder->index % coder->data->nb_dongles;
	if (coder->right_dongle)
	{
		coder->right_dongle = NULL;
		coder->data->dongles[right_index]->in_use = false;
		execute_action(coder, RELEASE);
	}
	if (coder->left_dongle)
	{
		coder->left_dongle = NULL;
		coder->data->dongles[left_index]->in_use = false;
	}
	pthread_cond_broadcast(&coder->data->cond);
	pthread_mutex_unlock(&coder->data->mutex);
}
