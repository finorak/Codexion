/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:40:58 by finorako          #+#    #+#             */
/*   Updated: 2026/04/21 11:03:07 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	is_digit(char *str)
{
	int	index;

	if (str[0] == '-')
		return (false);
	index = 0;
	if (str[0] == '+')
		index ++;
	while (str[index])
	{
		if (!('0' <= str[index] && str[index] <= '9'))
			return (false);
		index++;
	}
	return (true);
}

bool	ft_strcmp(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s1[index] || s2[index])
	{
		if (s1[index] != s2[index])
			return (false);
		index++;
	}
	return (true);
}

bool	is_valid(char *str)
{
	return (ft_strcmp(str, "fifo") || ft_strcmp(str, "edf"));
}
