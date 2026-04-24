/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 10:32:30 by finorako          #+#    #+#             */
/*   Updated: 2026/04/24 17:17:58 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdbool.h>

# define FILE_NAME "codexion"
# define ARG_ERROR "Arument must be valid\n"
# define ARG_MSG "run with ./%s number_of_coders time_to_burnout time_to_compile time_to_debug\
 time_to_refactor number_of_compiles_required dongle_cooldown scheduler\n"
# define INIT_ERROR "An error occured during initialisation!\n"
# define FIFO "fifo"
# define EDF "edf"
# define COMPILE "compil"
# define DEBUG "debugg"
# define REFACTOR "refactor"
# define TAKE_DONGLE "dongle"
# define RIGHT_DONGLE_NAME "dongle"
# define LEFT_DONGLE_NAME "dongle"
# define RELEASE "release"
# define RELEASE_DONGLE "%s %s\n"
# define BURNED_OUT "burned"
# define BURNED_OUT_MSG "%lld %d burned out\n"
# define CODE_LOG "%lld %d is %sing\n"
# define DONGLE_MSG "%lld %d has taken %s\n"

typedef struct s_data	t_data;
typedef struct s_coder	t_coder;

typedef struct s_wait_list
{
	struct s_wait_list	*next;
	t_coder				*coder;
}				t_wait_list;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_wait_list		*wait_list;
	long long		time_used;
	long long		cooldown;
	char			*name;
	bool			in_use;
}					t_dongle;

typedef struct s_coder
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_t		thread_id;
	long long		start_action_time;
	long long		dongle_cooldown;
	long long		refactor_time;
	long long		burnout_time;
	long long		compile_time;
	long long		debug_time;
	t_dongle		*right_dongle;
	t_dongle		*left_dongle;
	t_data			*data;
	int				dongle_count;
	int				compile_count;
	int				max_compile;
	int				index;
}					t_coder;

/*
 * mutex is used for monitoring
 * coders contain all the coder
 */
typedef struct s_data
{
	pthread_mutex_t	action_mutex;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	long long		dongle_cooldown;
	long long		refactor_time;
	long long		burnout_time;
	long long		compile_time;
	long long		debug_time;
	t_dongle		**dongles;
	t_coder			**coders;
	char			*scheduler;
	bool			fifo;
	int				available_dongle;
	int				compile_required;
	int				nb_dongles;
	int				nb_coders;
}					t_data;

long long			get_time(void);

t_coder				*create_coder(t_data *data);

t_dongle			*create_dongle(long long cooldown, char *dongle_name);

bool				arg_checker(char **av, int size);

void				parser(char **av, t_data *data);

void				print_log(t_coder *coder, char *action);

void				request_dongle(t_coder *coder, int coder_index);

void				take_requested_dongle(t_coder *coder);

void				release_dongle(t_coder *coder);

bool				init(t_data *data);

void				simulate(void *data);

void				join_thread(t_data *data);

void				free_memory(t_data *data);

void				*activate_coder(void *arg);

void				execute_action(t_coder *coder, char *action);

int					ft_strcmp(char *s1, char *s2);
#endif
