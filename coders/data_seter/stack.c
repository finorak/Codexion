/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:26:39 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 19:05:21 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../codexion.h"

char	*ft_strdup(char *str)
{
	char	*value;
	int		index;

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
	dongle->name = ft_strdup(dongle_name);
	return (dongle);
}

t_coder	*create_coder(t_data *data)
{
	t_coder	*coder;

	coder = (t_coder *)malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->data = data;
	coder->right_dongle = create_dongle(data->dongle_cooldown,
			RIGHT_DONGLE_NAME);
	coder->left_dongle = create_dongle(data->dongle_cooldown,
			LEFT_DONGLE_NAME);
	return (coder);
}
