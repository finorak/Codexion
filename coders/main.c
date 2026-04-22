/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 08:54:59 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 13:58:11 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 9)
	{
		printf(ARG_MSG, FILE_NAME);
		return (1);
	}
	if (!arg_checker(av + 1, ac - 1))
		return (1);
	parser(av + 1, &data);
	if (!init(&data))
	{
		printf(INIT_ERROR);
		return (1);
	}
	join_thread(&data);
	free_memory(&data);
	return (0);
}
