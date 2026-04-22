/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:34:41 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 16:52:20 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../codexion.h"

t_dongle	*get_current_dongle(t_coder *coder)
{
	return (coder->left_dongle);
}

void	print_log(t_coder *coder, char *action)
{
	t_dongle	*curr_dongle;

	curr_dongle = get_current_dongle(coder);
	if (!ft_strcmp(COMPILE, action))
		printf(CODE_LOG, (long long)50, coder->index, action);
	else if (!ft_strcmp(DEBUG, action))
		printf(CODE_LOG, (long long)50, coder->index, action);
	else if (!ft_strcmp(REFACTOR, action))
		printf(CODE_LOG, (long long)50, coder->index, action);
	else if (!ft_strcmp(TAKE_DONGLE, action))
		printf(DONGLE_MSG, (long long)50, coder->index, curr_dongle->name);
}
