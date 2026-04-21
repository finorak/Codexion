/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:03:29 by finorako          #+#    #+#             */
/*   Updated: 2026/04/21 12:14:35 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"
#include "../coders/stack_utils.h"
#include "../coders/memory_header.h"

t_coders	*create_coders(int nb_coders)
{
	t_coders	*coders;
	t_coders	*new_node;
	int			index;

	coders = NULL;
	new_node = NULL;
	index = 0;
	while (index < nb_coders)
	{
		new_node = new_stack(index + 1);
		if (!new_node)
		{
			free_memory(&coders);
			return (NULL);
		}
		addback(&coders, new_node);
		index++;
	}
	return (coders);
}
