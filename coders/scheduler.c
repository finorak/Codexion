/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:45:26 by finorako          #+#    #+#             */
/*   Updated: 2026/05/20 10:52:44 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdbool.h>

static bool	fifo_scheduler(t_coder *coder,
		t_queue *first_queue, t_queue *second_queue)
{
	if (!first_queue | !second_queue)
		return (false);
	insert(&coder->first_dongle->queue, first_queue, coder->first_dongle);
	insert(&coder->second_dongle->queue, second_queue, coder->second_dongle);
	if (!is_first(coder->first_dongle->queue, coder, coder->first_dongle)
		|| !is_first(coder->second_dongle->queue, coder, coder->second_dongle))
	{
		pop_first(&coder->first_dongle->queue, coder->first_dongle);
		pop_first(&coder->second_dongle->queue, coder->second_dongle);
		return (false);
	}
	return (true);
}

static bool	edf_scheduler(t_coder *coder,
		t_queue *first_queue, t_queue *second_queue)
{
	if (!first_queue | !second_queue)
		return (false);
	(void)coder;
	return (true);
}

bool	scheduler(t_coder *coder, t_queue *first_queue, t_queue *second_queue)
{
	if (coder->data->fifo_scheduler)
		return (fifo_scheduler(coder, first_queue, second_queue));
	return (edf_scheduler(coder, first_queue, second_queue));
}
