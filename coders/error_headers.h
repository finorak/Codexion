/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_headers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:52:56 by finorako          #+#    #+#             */
/*   Updated: 2026/04/21 12:20:48 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HEADERS_H
# define ERROR_HEADERS_H

# include "coders.h"
# include <stdbool.h>

bool	is_digit(char *str);

bool	is_valid(char *str);

bool	arg_is_valid(char **av, int size, t_coders_info *info);

#endif
