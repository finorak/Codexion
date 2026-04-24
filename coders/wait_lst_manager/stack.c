/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:13:02 by finorako          #+#    #+#             */
/*   Updated: 2026/04/24 17:24:11 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../codexion.h"

t_wait_list	*que(t_coder *coder)
{
	t_wait_list	*waiter;

	waiter = (t_wait_list *)malloc(sizeof(t_wait_list));
	if (!waiter)
		return (NULL);
	waiter->coder = coder;
	waiter->next = NULL;
	return (waiter);
}

void	add_to_waitlist(t_wait_list **lst, t_wait_list *que)
{
	t_wait_list	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = que;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = que;
}
