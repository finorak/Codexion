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

#include <unistd.h>
#include "codexion.h"

static void	ft_sleep(long time_to_sleep)
{
	long	start;

	start = get_current_time();
	while (get_current_time() - start < time_to_sleep)
		usleep(100);
}

static bool	single_coder(char **av)
{
	long	start;

	start = get_current_time();
	printf("0 1 has takken a dongle\n");
	ft_sleep(atoi(av[2]));
	printf("%ld 1 burned out\n", get_current_time() - start + 1);
	return (false);
}

static bool	valid_arg(int ac, char **av, t_data *data)
{
	if (ac != 9)
	{
		fprintf(stderr, "Argument error!\n");
		return (false);
	}
	if (!arg_checker(av + 1))
	{
		fprintf(stderr, "Argument error!\n");
		return (false);
	}
	if (atoi(av[1]) == 1)
		return (single_coder(av));
	if (!parse_data(data, av + 1))
	{
		fprintf(stderr, "Time value must be >= "
			"%dms each and nb_coders >= %d and nb_dongles >= %d\n",
			MIN_TIME, MIN_CODERS, MIN_DONGLES);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!valid_arg(ac, av, &data))
		return (1);
	init_data(&data);
	init_thread(&data);
	join_thread(&data);
	cleanup(&data);
	return (0);
}
