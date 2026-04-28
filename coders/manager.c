/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 22:45:06 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 10:53:55 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/*
	only make the newly added coder take a fork
	if it's the first in line
*/

bool	insert(t_queue **queue, t_queue *new_queue, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (!queue)
		return (false);
	addback(queue, new_queue);
	pthread_mutex_unlock(mutex);
	return (true);
}

void	pop_first(t_queue **queue)
{
	t_queue	*temp;

	if (!queue || !*queue)
		return ;
	temp = *queue;
	*queue = (*queue)->next;
	free(temp);
}
