/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:14:40 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 12:23:40 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	join_thread(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		pthread_join(data->coders[index].thread_id, NULL);
		index++;
	}
}
