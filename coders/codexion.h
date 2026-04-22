/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:32:30 by finorako          #+#    #+#             */
/*   Updated: 2026/04/22 19:05:54 by finorako         ###   ########.fr       */
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
# define COMPILE "compil"
# define DEBUG "debugg"
# define REFACTOR "refactor"
# define CODE_LOG "%lld %d is %sing\n"
# define TAKE_DONGLE "dongle"
# define RIGHT_DONGLE_NAME "right dongle"
# define LEFT_DONGLE_NAME "left dongle"
# define DONGLE_MSG "%lld %d has taken %s\n"

typedef struct s_data	t_data;

typedef struct s_dongle
{
	long long	cooldown;
	char		*name;
}					t_dongle;

typedef struct s_coder
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_t		thread_id;
	t_dongle		*right_dongle;
	t_dongle		*left_dongle;
	t_data			*data;
	int				max_compile;
	int				index;
}					t_coder;

/*
 * mutex is used for monitoring
 * coders contain all the coder
 */
typedef struct s_data
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	long long		burnout_time;
	long long		compile_time;
	long long		debug_time;
	long long		refactor_time;
	long long		dongle_cooldown;
	t_dongle		*dongles;
	t_coder			**coders;
	char			*scheduler;
	int				nb_coders;
	int				nb_dongles;
	int				compile_required;
}					t_data;

long long			get_time(void);

t_coder				*create_coder(t_data *data);

bool				arg_checker(char **av, int size);

void				parser(char **av, t_data *data);

void				print_log(t_coder *coder, char *action);

bool				init_coders(t_data *data);

bool				init(t_data *data);

void				simulate(void *data);

void				join_thread(t_data *data);

void				free_memory(t_data *data);

void				*activate_coder(void *arg);

int					ft_strcmp(char *s1, char *s2);
#endif
