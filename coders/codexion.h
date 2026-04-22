/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:32:30 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 13:56:00 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdbool.h>

# define FILE_NAME "codexion"
# define ARG_MSG "run with ./%s number_of_coders time_to_burnout time_to_compile time_to_debug\
 time_to_refactor number_of_compiles_required dongle_cooldown scheduler\n"
# define INIT_ERROR "An error occured during initialisation!\n"
# define FIFO "fifo"
# define EDF "edf"

typedef struct s_data	t_data;

typedef struct s_coder
{
	pthread_mutex_t	mutex;
	pthread_t		thread_id;
	t_data			*data;
}					t_coder;

typedef struct s_data
{
	pthread_mutex_t	mutex;
	long long		burnout_time;
	long long		compile_time;
	long long		debug_time;
	long long		refactor_time;
	long long		dongle_cooldown;
	t_coder			*coders;
	char			*scheduler;
	int				nb_coders;
	int				nb_dongles;
	int				compile_required;
}					t_data;

bool				arg_checker(char **av, int size);

void				parser(char **av, t_data *data);

bool				init_coders(t_data *data);

t_coder				create_coder(t_data *data);

bool				init(t_data *data);

void				join_thread(t_data *data);

void				free_memory(t_data *data);

#endif
