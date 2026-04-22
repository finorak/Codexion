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

void	print_log(t_coder coder, char *action)
{
	if (!ft_strcmp(COMPILE, action))
		printf(CODE_LOG, (long long)50, coder.index, action);
	else if (!ft_strcmp(DEBUG, action))
		printf(CODE_LOG, (long long)50, coder.index, action);
	else if (!ft_strcmp(REFACTOR, action))
		printf(CODE_LOG, (long long)50, coder.index, action);
	else if (!ft_strcmp(TAKE_DONGLE, action))
		printf("%lld %d has taken a dongle\n", (long long)50, coder.index);
}
