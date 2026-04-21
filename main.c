/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 08:58:38 by finorako          #+#    #+#             */
/*   Updated: 2026/04/21 12:33:04 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"
#include "coders/error_headers.h"
#include "coders/memory_header.h"
#include "coders/util_header.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_coders_info	info;
	t_coders		*coders;

	coders = NULL;
	if (ac != 9)
		return (1);
	if (!arg_is_valid(av + 1, ac - 1, &info))
	{
		printf("Arg invalid\n");
		return (1);
	}
	coders = create_coders(atoi(av[1]));
	free_memory(&coders);
	return (0);
}
