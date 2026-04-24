/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:34:41 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 16:52:20 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include "../codexion.h"

long long	get_time(void)
{
	struct timeval	curr_time;
	long long		time_mls;

	gettimeofday(&curr_time, NULL);
	time_mls = (long long)(curr_time.tv_sec) *1000000 + curr_time.tv_usec;
	return (time_mls);
}

void	print_log(t_coder *coder, char *action)
{
	long long	elapsed_time;

	elapsed_time = get_time() - coder->start_action_time;
	if (!ft_strcmp(COMPILE, action))
		printf(CODE_LOG, elapsed_time, coder->index, action);
	else if (!ft_strcmp(DEBUG, action))
		printf(CODE_LOG, elapsed_time, coder->index, action);
	else if (!ft_strcmp(REFACTOR, action))
		printf(CODE_LOG, elapsed_time, coder->index, action);
	else if (!ft_strcmp(TAKE_DONGLE, action))
		printf(DONGLE_MSG, elapsed_time, coder->index, RIGHT_DONGLE_NAME);
	else if (!ft_strcmp(RELEASE, action))
		printf(RELEASE_DONGLE, "right", LEFT_DONGLE_NAME);
}
