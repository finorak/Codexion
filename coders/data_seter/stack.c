/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:26:39 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 12:58:38 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_coder	create_coder(t_data *data)
{
	t_coder	coder;

	coder.data = data;
	return (coder);
}
