/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:27:47 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 08:33:16 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "codexion.h"

static bool	is_numeric(char *str)
{
	long	value;
	int		index;

	index = 0;
	value = 0;
	while ((8 <= str[index] && str[index] <= 13) || str[index] == 32)
		index++;
	if (str[index] == '-')
		return (false);
	if (str[index] == '+')
		index++;
	if (!str[index])
		return (false);
	if (ft_strlen(str + index) > 10)
		return (false);
	while (ft_isdigit(str[index]))
	{
		value = (value * 10) + (str[index] - '0');
		index++;
	}
	return (value < INT_MAX);
}

bool	arg_checker(char **av)
{
	int	index;

	index = 0;
	while (index < 7)
	{
		if (!is_numeric(av[index]))
			return (false);
		index++;
	}
	return (!ft_strcmp(av[index], FIFO) || !ft_strcmp(av[index], EDF));
}

bool	parse_data(t_data *data, char **av)
{
	data->nb_coders = atoi(av[0]);
	data->nb_dongles = atoi(av[0]);
	data->time.burnout = atoi(av[1]);
	data->time.compile = atoi(av[2]);
	data->time.debug = atoi(av[3]);
	data->time.refactor = atoi(av[4]);
	data->compile_required = atoi(av[5]);
	data->time.cooldown = atoi(av[6]);
	data->scheduler = av[7];
	data->burned_out = false;
	data->time.start_time = get_current_time();
	return (data->nb_coders >= 1 && data->time.burnout >= 60
		&& data->time.compile >= 60 && data->time.refactor >= 60
		&& data->time.debug >= 60);
}
