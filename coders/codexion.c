/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:56:47 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 10:35:10 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "codexion.h"

static void	coder_routing(t_coder *coder)
{
	if (!request_dongle(coder))
		return ;
	update_coder_state(coder);
	print_log(coder, COMPILE);
	busy_sleep(coder->data, coder->data->time.compile);
	release_dongle(coder);
	update_coder_burning_state(coder, true);
	print_log(coder, DEBUG);
	busy_sleep(coder->data, coder->data->time.debug);
	if (simulation_done(coder->data))
		return ;
	print_log(coder, REFACTOR);
	busy_sleep(coder->data, coder->data->time.refactor);
}

void	*coder_thread(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	update_thread_active(coder->data);
	if (coder->data->nb_coders % 2 != 0)
	{
		if (coder->index % 2 == 0)
			usleep(200);
	}
	while (!coder_done_coding(coder) && !simulation_done(coder->data))
		coder_routing(coder);
	return (NULL);
}
