/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 19:28:50 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 10:07:05 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "codexion.h"

static bool	is_burnout(t_data *data, int index)
{
	if (coder_burned_out(data->coders[index]))
	{
		data->burned_out = true;
		print_log(data->coders[index], BURNOUT);
		pthread_mutex_unlock(&data->lock);
		return (true);
	}
	return (false);
}

void	*monitoring_thread(void *arg)
{
	t_data	*data;
	int		index;

	data = (t_data *)arg;
	while (true)
	{
		index = 0;
		pthread_mutex_lock(&data->lock);
		while (index < data->nb_coders)
		{
			if (all_coder_done(data))
			{
				pthread_mutex_unlock(&data->lock);
				return (NULL);
			}
			if (is_burnout(data, index))
				return (NULL);
			index++;
		}
		pthread_mutex_unlock(&data->lock);
		busy_sleep(1);
	}
	return (NULL);
}
