/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 18:14:44 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 19:58:08 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"
#include <bits/types/struct_timeval.h>
#include <stdio.h>

static void	execute_action(t_coder *coder, char *action)
{
	pthread_mutex_lock(&coder->data->mutex);
	if (!ft_strcmp(COMPILE, action))
		print_log(coder, action);
	else if (!ft_strcmp(DEBUG, action))
		print_log(coder, action);
	else if (!ft_strcmp(REFACTOR, action))
		print_log(coder, action);
	pthread_mutex_unlock(&coder->data->mutex);
}

bool	coders_active(t_data *data)
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
}

void	*activate_coder(void *arg)
{
	t_coder			*coder;

	coder = (t_coder *)arg;
	execute_action(coder, COMPILE);
	execute_action(coder, DEBUG);
	execute_action(coder, REFACTOR);
	return (NULL);
}
