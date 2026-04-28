/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:13:08 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 06:16:59 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	assigne_dongle(t_coder *coder)
{
	int	first;
	int	second;

	first = coder->index;
	second = first % coder->data->nb_coders;
	coder->first_dongle = coder->data->dongles[first - 1];
	coder->second_dongle = coder->data->dongles[second];
	if (first % 2 == 0)
	{
		coder->first_dongle = coder->data->dongles[second];
		coder->second_dongle = coder->data->dongles[first - 1];
	}
}

static t_coder	**coders(t_data *data)
{
	t_coder	**coderlst;
	int		index;

	coderlst = (t_coder **)malloc(sizeof(t_coder *) * data->nb_coders);
	if (!coderlst)
		return (NULL);
	index = 0;
	while (index < data->nb_coders)
	{
		coderlst[index] = newcoder(data, index);
		if (!coderlst[index])
		{
			free_coders(coderlst, index);
			return (NULL);
		}
		assigne_dongle(coderlst[index]);
		index++;
	}
	return (coderlst);
}

static t_dongle	**dongles(t_data *data)
{
	t_dongle	**donglelst;
	int			index;

	donglelst = (t_dongle **)malloc(sizeof(t_dongle *) * data->nb_dongles);
	if (!donglelst)
		return (NULL);
	index = 0;
	while (index < data->nb_dongles)
	{
		donglelst[index] = newdongle(index);
		if (!donglelst[index])
		{
			free_dongles(donglelst, index);
			return (NULL);
		}
		index++;
	}
	return (donglelst);
}

void	init_data(t_data *data)
{
	if (!data)
		return ;
	data->dongles = dongles(data);
	if (!data->dongles)
		return ;
	data->coders = coders(data);
	if (!data->coders)
		return ;
	data->thread_activated = 0;
	data->coder_done = 0;
	data->error_occured = false;
}
