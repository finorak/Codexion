/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:26:39 by finorako          #+#    #+#             */
/*   Updated: 2026/04/24 14:22:40 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "../codexion.h"

static char	*ft_strdup(char *str)
{
	char	*value;
	int		index;

	if (!str)
		return (NULL);
	index = 0;
	while (str[index])
		index++;
	value = (char *)malloc(sizeof(char) * (index + 1));
	if (!value)
		return (NULL);
	index = 0;
	while (str[index])
	{
		value[index] = str[index];
		index++;
	}
	value[index] = '\0';
	return (value);
}

t_dongle	*create_dongle(long long cooldown, char *dongle_name)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->cooldown = cooldown;
	dongle->wait_list = NULL;
	dongle->name = ft_strdup(dongle_name);
	dongle->in_use = false;
	if (!dongle->name)
	{
		free(dongle);
		return (NULL);
	}
	return (dongle);
}

t_coder	*create_coder(t_data *data)
{
	t_coder	*coder;

	coder = (t_coder *)malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->data = data;
	coder->dongle_count = 0;
	coder->compile_time = data->compile_time;
	coder->debug_time = data->debug_time;
	coder->left_dongle = NULL;
	coder->right_dongle = NULL;
	return (coder);
}
