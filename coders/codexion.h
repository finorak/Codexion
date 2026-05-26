/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: finorako <finorako@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:25:52 by finorako          #+#    #+#             */
/*   Updated: 2026/05/20 13:43:16 by finorako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

// scheduler
# define FIFO "fifo"
# define EDF "edf"

// action to perform
# define COMPILE "compile"
# define DEBUG "debug"
# define REFACTOR "refactor"
# define TAKE "take"
# define BURNOUT "burnout"
# define REQUEST "request"

// MINIMUM FOR SETTINGS
# define MIN_TIME 10
# define MIN_CODERS 1
# define MIN_DONGLES 1

// Just to tell the compiler that
// we have those struct in our code
typedef struct s_queue	t_queue;
typedef struct s_data	t_data;
typedef struct s_coder	t_coder;

// containing all about the time
typedef struct s_time
{
	long				start_time;
	long				burnout;
	long				compile;
	long				debug;
	long				refactor;
	long				cooldown;
}						t_time;

// the que struct, we use this to avoid starvation
typedef struct s_queue
{
	struct s_queue		*next;
	t_coder				*coder;
	int					id;
}						t_queue;

// contain the dongle's data
typedef struct s_dongle
{
	pthread_mutex_t		queue_lock;
	pthread_mutex_t		lock;
	pthread_cond_t		cond;
	t_queue				*queue;
	long				last_cooldown_time;
	int					index;
}						t_dongle;

// contain the coder's data
typedef struct s_coder
{
	pthread_t			thread_id;
	t_dongle			*first_dongle;
	t_dongle			*second_dongle;
	t_data				*data;
	bool				is_burning;
	long				last_compile_time;
	long				last_compile_start;
	int					compile_count;
	int					index;
}						t_coder;

// conain the main data of the program
typedef struct s_data
{
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		lock;
	pthread_t			thread_id;
	t_dongle			**dongles;
	t_coder				**coders;
	t_time				time;
	char				*scheduler;
	bool				fifo_scheduler;
	bool				error_occured;
	bool				burned_out;
	int					coder_done;
	int					nb_coders;
	int					nb_dongles;
	int					compile_required;
	int					thread_activated;
}						t_data;

// ft functions
bool					ft_isdigit(char c);
bool					ft_isspace(char c);
int						ft_strlen(char *str);
int						ft_strcmp(char *s1, char *s2);

// argument functions
bool					arg_checker(char **av);
bool					parse_data(t_data *data, char **av);

// coder functions for thread
void					update_thread_active(t_data *data);
void					*coder_thread(void *arg);
bool					coder_done_coding(t_coder *coder);
bool					simulation_done(t_data *data);
bool					coder_burned_out(t_coder *coder);
bool					all_coder_done(t_data *data);
int						thread_activated(t_data *data);
void					*monitoring_thread(void *arg);
void					update_coder_state(t_coder *coder);
void					update_coder_burning_state(t_coder *coder, bool value);
void					update_coder_last_compile_start(t_coder *coder);
long					coder_compile_start(t_coder *coder);

// scheduler functions
bool					scheduler(t_coder *coder,
							t_queue *first_queue, t_queue *second_queue);

// dongle manager functions
bool					request_dongle(t_coder *coder);
void					release_dongle(t_coder *coder);
bool					dongle_is_available(t_dongle *dongle, t_coder *coder);

// queue manager functions
t_queue					*newqueue(t_coder *coder);
bool					is_first(t_queue *queue, t_coder *coder);
void					addback(t_queue **queue, t_queue *new_queue);
bool					insert(t_queue **queue, t_queue *new_queue,
							t_dongle *dongle);
void					swap_coder(t_queue **queue);
void					pop_first(t_queue **queue, t_dongle *dongle);
void					pop_last(t_queue **queue, t_dongle *dongle);
void					based_insert(t_queue **queue, t_coder *coder,
							t_dongle *dongle);

// init functions
t_dongle				*newdongle(int index);
t_coder					*newcoder(t_data *data, int index);
void					init_data(t_data *data);
void					init_thread(t_data *data);
void					join_thread(t_data *data);

// bench functions utilities
void					print_log(t_coder *coder, char *action);
long					get_current_time(void);
void					busy_sleep(t_data *data, long time_to_sleep);

// memory managment
void					free_coders(t_coder **coder, int size);
void					free_dongles(t_dongle **dongles, int size);
void					cleanup(t_data *data);

// debuger
void					print_data(t_data *data);
void					print_waitlst(t_queue *queue);
void					print_coder_state(t_coder *coder);
#endif
