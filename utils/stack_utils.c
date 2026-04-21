/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:08:58 by finorako          #+#    #+#             */
/*   Updated: 2026/04/21 12:37:27 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../coders/coders.h"

t_coders	*new_stack(int index)
{
	t_coders	*coders;

	coders = (t_coders *)malloc(sizeof(t_coders));
	if (!coders)
		return (NULL);
	coders->index = index;
	coders->next = NULL;
	return (coders);
}

void	addback(t_coders **lst, t_coders *new_coder)
{
	t_coders	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new_coder;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_coder;
}
