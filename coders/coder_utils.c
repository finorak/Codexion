/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 19:48:36 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 08:22:33 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdbool.h>

bool	coder_done_coding(t_coder *coder)
{
	return (coder->compile_count == coder->data->compile_required);
}

bool	coder_burned_out(t_coder *coder)
{
	return (get_current_time() - coder->last_compile_time
		> coder->data->time.burnout);
}

void	update_coder_state(t_coder *coder)
{
	pthread_mutex_lock(&coder->data->lock);
	coder->last_compile_time = get_current_time();
	coder->compile_count += 1;
	pthread_mutex_unlock(&coder->data->lock);
}

bool	is_first(t_queue *queue, t_coder *coder)
{
	bool	first;

	first = false;
	pthread_mutex_lock(&coder->data->lock);
	if (!queue)
		first = false;
	else
		first = queue->coder == coder;
	pthread_mutex_lock(&coder->data->lock);
	return (first);
}

bool	all_coder_done(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		if (!coder_done_coding(data->coders[index]))
			return (false);
		index++;
	}
	return (true);
}
