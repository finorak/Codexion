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

static void	compile(t_coder *coder)
{
	request_dongle(coder);
	busy_sleep(coder->data->time.compile);
	update_coder_state(coder);
	print_log(coder, COMPILE);
}

static void	debug(t_coder *coder)
{
	busy_sleep(coder->data->time.debug);
	print_log(coder, DEBUG);
}

static void	refactor(t_coder *coder)
{
	busy_sleep(coder->data->time.refactor);
	print_log(coder, REFACTOR);
}

void	*coder_thread(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	update_thread_active(coder->data);
	if (coder->index % 2 == 0)
		usleep(200);
	while (!coder_done_coding(coder))
	{
		if (simulation_done(coder->data))
			return (NULL);
		compile(coder);
		debug(coder);
		refactor(coder);
		release_dongle(coder);
	}
	return (NULL);
}
