/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:44:53 by finorako          #+#    #+#             */
/*   Updated: 2026/04/21 12:28:39 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../coders/coders.h"

void	free_memory(t_coders **coders)
{
	t_coders	*temp;

	while (*coders)
	{
		temp = (*coders)->next;
		free(*coders);
		*coders = temp;
	}
}
