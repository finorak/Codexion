/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:10:39 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 16:17:41 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>

long long	get_time(void)
{
	struct timeval	curr_time;
	long long		time_mls;

	gettimeofday(&curr_time, NULL);
	time_mls = (long long)(curr_time.tv_sec) *1000 + (curr_time.tv_sec / 1000);
	return (time_mls);
}
