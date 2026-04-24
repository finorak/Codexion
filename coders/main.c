/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 08:54:59 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 19:02:01 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "codexion.h"

static bool	codexion(int ac, char **av, t_data *data)
{
	if (ac != 9)
	{
		fprintf(stderr, ARG_MSG, FILE_NAME);
		return (false);
	}
	if (!arg_checker(av + 1, ac - 1))
	{
		fprintf(stderr, ARG_ERROR);
		return (false);
	}
	parser(av + 1, data);
	if (!init(data))
	{
		fprintf(stderr, INIT_ERROR);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.coders = NULL;
	data.dongles = NULL;
	if (!codexion(ac, av, &data))
		return (1);
	join_thread(&data);
	free_memory(&data);
	return (0);
}
