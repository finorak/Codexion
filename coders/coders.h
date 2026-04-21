/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 09:39:12 by finorako          #+#    #+#             */
/*   Updated: 2026/04/21 12:17:38 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H

# define CODERS_H

# include <pthread.h>

typedef struct s_coders_info
{
	char			*scheduler;
	int				burnout_time;
	int				compile_time;
	int				debug_time;
	int				refactor_time;
	int				compile_required;
	int				dongle_cooldown;
}					t_coders_info;

typedef struct s_thread_info
{
	t_coders_info	*coder_info;
	pthread_t		thread_id;
}					t_thread_info;

typedef struct s_coders
{
	struct s_coders	*next;
	t_thread_info	*thread_info;
	int				index;
}					t_coders;

#endif
