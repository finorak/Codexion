/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:08:31 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 19:08:33 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	request_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->mutex);
	pthread_mutex_unlock(&coder->data->mutex);
}

void	release_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->mutex);
	coder->data->available_dongle += 1;
	pthread_mutex_unlock(&coder->data->mutex);
}
