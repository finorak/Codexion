/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:06:47 by finorako          #+#    #+#             */
/*   Updated: 2026/05/05 16:31:52 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "codexion.h"

void	busy_sleep(t_data *data, long time_to_sleep)
{
	long	start;

	start = get_current_time();
	while (!simulation_done(data) && get_current_time() - start < time_to_sleep)
		usleep(100);
}

long	get_current_time(void)
{
	struct timeval	tv;
	long			curr_time;

	gettimeofday(&tv, NULL);
	curr_time = (long)(tv.tv_sec * 1e3) + (tv.tv_usec / 1e3);
	return (curr_time);
}

void	print_log(t_coder *coder, char *action)
{
	long	elapsed;

	elapsed = get_current_time() - coder->data->time.start_time;
	if (ft_strcmp(action, BURNOUT) != 0 && simulation_done(coder->data))
		return ;
	pthread_mutex_lock(&coder->data->print_mutex);
	if (!ft_strcmp(action, TAKE))
		printf("%ld %d has taken a dongle\n", elapsed, coder->index);
	else if (!ft_strcmp(action, COMPILE))
		printf("%ld %d is compiling\n", elapsed, coder->index);
	else if (!ft_strcmp(action, DEBUG))
		printf("%ld %d is debugging\n", elapsed, coder->index);
	else if (!ft_strcmp(action, REFACTOR))
		printf("%ld %d is refactoring\n", elapsed, coder->index);
	else if (!ft_strcmp(action, BURNOUT))
		printf("%ld %d burned out\n", elapsed, coder->index);
	else if (!ft_strcmp(action, POSIION_STATE))
		printf("is_first: %d\n", is_first(coder->first_dongle->queue, coder));
	else if (!ft_strcmp(action, REQUEST))
		printf("%ld %d has request a dongle\n", elapsed, coder->index);
	pthread_mutex_unlock(&coder->data->print_mutex);
}
