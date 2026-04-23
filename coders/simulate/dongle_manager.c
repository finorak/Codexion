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
	pthread_mutex_lock(&coder->mutex);
	coder->dongle_count += 1;
	pthread_mutex_unlock(&coder->mutex);
}

void	take_requested_dongle(t_coder *coder)
{
	(void)coder;
	return ;
}

void	release_dongle(t_coder *coder)
{
	coder->dongle_count -= 1;
	return ;
}
