/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:14:44 by finorako          #+#    #+#             */
/*   Updated: 2026/04/24 13:51:01 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../codexion.h"

static void	execute_action(t_coder *coder, char *action)
{
	pthread_mutex_lock(&coder->data->action_mutex);
	coder->start_action_time = get_time();
	if (!ft_strcmp(COMPILE, action))
		print_log(coder, action);
	else if (!ft_strcmp(DEBUG, action))
		print_log(coder, action);
	else if (!ft_strcmp(REFACTOR, action))
		print_log(coder, action);
	else if (!ft_strcmp(TAKE_DONGLE, action))
		print_log(coder, action);
	usleep(100000);
	pthread_mutex_unlock(&coder->data->action_mutex);
}

/*static bool	coders_active(t_data *data)
{
	int				index;

	index = 0;
	while (index < data->nb_coders)
	{
		if (data->coders[index]->max_compile >= data->compile_required)
			return (false);
		index++;
	}
	return (true);
}*/

void	*activate_coder(void *arg)
{
	t_coder			*coder;

	coder = (t_coder *)arg;
	request_dongle(coder);
	execute_action(coder, TAKE_DONGLE);
	execute_action(coder, COMPILE);
	execute_action(coder, DEBUG);
	execute_action(coder, REFACTOR);
	return (NULL);
}
