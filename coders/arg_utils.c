/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:27:47 by finorako          #+#    #+#             */
/*   Updated: 2026/05/05 16:32:58 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>
#include <stdbool.h>

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
	while (ft_isdigit(str[index]))
	{
		value = (value * 10) + (str[index] - '0');
		index++;
	}
	return (value < INT_MAX);
}

bool	is_valid(char *str)
{
	bool	valid;
	int		index;

	index = 0;
	valid = false;
	while (str[index] && ft_isspace(str[index]))
		index++;
	if (!str[index] || str[index] == '-')
		return (valid);
	if (str[index] == '+')
		index++;
	while (str[index] && ft_isdigit(str[index]))
	{
		valid = true;
		index++;
	}
	if (valid && str[index])
		return (false);
	return (valid);
}

bool	arg_checker(char **av)
{
	int	index;

	index = 0;
	while (index < 7)
	{
		if (!is_valid(av[index]))
			return (false);
		if (!is_numeric(av[index]))
			return (false);
		index++;
	}
	return (!ft_strcmp(av[index], FIFO) || !ft_strcmp(av[index], EDF));
}

bool	parse_data(t_data *data, char **av)
{
	data->counter.nb_coders = atoi(av[0]);
	data->counter.nb_dongles = atoi(av[0]);
	data->time.burnout = atoi(av[1]);
	data->time.compile = atoi(av[2]);
	data->time.debug = atoi(av[3]);
	data->time.refactor = atoi(av[4]);
	data->counter.compile_required = atoi(av[5]);
	data->time.cooldown = atoi(av[6]);
	data->scheduler = av[7];
	data->burned_out = false;
	return (data->counter.nb_coders >= MIN_CODERS
		&& data->time.burnout >= MIN_TIME && data->time.compile >= MIN_TIME
		&& data->time.refactor >= MIN_TIME && data->time.debug >= MIN_TIME
		&& data->time.cooldown >= MIN_TIME
		&& data->counter.nb_dongles >= MIN_DONGLES
		&& data->counter.compile_required >= MIN_COMPILE_REQUIRED);
}
