/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:48:44 by finorako          #+#    #+#             */
/*   Updated: 2026/04/21 12:32:42 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "../../coders/error_headers.h"
#include "../../coders/coders.h"

char	*ft_strdup(char *str)
{
	char	*value;
	int		index;

	index = 0;
	while (str[index])
		index++;
	value = (char *)malloc(sizeof(char) * (index + 1));
	if (!str)
		return (NULL);
	index = 0;
	while (str[index])
	{
		value[index] = str[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}

bool	arg_is_valid(char **av, int size, t_coders_info *info)
{
	int	index;

	index = 0;
	while (av[index] && index < size - 1)
	{
		if (!is_digit(av[index]))
			return (false);
		index++;
	}
	if (!is_valid(av[index]))
		return (false);
	info->burnout_time = atoi(av[1]);
	info->compile_time = atoi(av[2]);
	info->debug_time = atoi(av[3]);
	info->refactor_time = atoi(av[4]);
	info->compile_required = atoi(av[5]);
	info->dongle_cooldown = atoi(av[6]);
	info->scheduler = av[7];
	return (true);
}
