/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:00:14 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 19:07:13 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../codexion.h"

void	release(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		pthread_mutex_destroy(&data->coders[index]->mutex);
		free(data->coders[index]);
		index++;
	}
}

void	free_memory(t_data *data)
{
	release(data);
	free(data->coders);
}
