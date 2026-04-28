/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:24:53 by finorako          #+#    #+#             */
/*   Updated: 2026/04/28 08:34:19 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

// print_data(&data);
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 9)
	{
		fprintf(stderr, "Argument error!\n");
		return (1);
	}
	if (!arg_checker(av + 1))
	{
		fprintf(stderr, "Argument error!\n");
		return (1);
	}
	if (!parse_data(&data, av + 1))
	{
		fprintf(stderr, "Those value must be at least "
			"60ms each and nb_coder >= 1\n");
		return (1);
	}
	init_data(&data);
	init_thread(&data);
	join_thread(&data);
	cleanup(&data);
	return (0);
}
