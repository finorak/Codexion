/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:45:45 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 17:15:02 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../codexion.h"

static bool	ft_isdigit(char *str)
{
	int	index;

	if (str[0] == '-')
		return (false);
	index = 0;
	if (str[0] == '+')
		index++;
	if (!str[index])
		return (false);
	while (str[index])
	{
		if (!('0' <= str[index] && str[index] <= '9'))
			return (false);
		index++;
	}
	return (true);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s1[index] || s2[index])
	{
		if (s1[index] != s2[index])
			return (s1[index] - s2[index]);
		index++;
	}
	return (0);
}

bool	arg_checker(char **av, int size)
{
	int	index;

	index = 0;
	while (index < size -1)
	{
		if (!ft_isdigit(av[index]))
			return (false);
		index++;
	}
	if (!ft_strcmp(av[index], FIFO) || !ft_strcmp(av[index], EDF))
		return (true);
	return (false);
}

static long long	time_parser(char *str)
{
	long long	value;
	int			index;

	value = 0;
	index = 0;
	while (str[index])
	{
		value = (value * 10) + (str[index] - '0');
		index++;
	}
	return (value);
}

void	parser(char **av, t_data *data)
{
	data->nb_coders = atoi(av[0]);
	data->nb_dongles = atoi(av[0]);
	data->burnout_time = time_parser(av[1]);
	data->compile_time = time_parser(av[2]);
	data->debug_time = time_parser(av[3]);
	data->refactor_time = time_parser(av[4]);
	data->compile_required = atoi(av[5]);
	data->dongle_cooldown = time_parser(av[6]);
	data->scheduler = av[7];
}
