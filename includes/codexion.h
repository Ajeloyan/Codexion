/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 01:50:57 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/08 22:19:27 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

typedef struct s_request
{
	int				coder_id;
	long long		timestamp;
	long long		score;
}					t_request;

typedef struct s_queue
{
	t_request		*request;
	int				size;
	int				capacity;
}					t_queue;

typedef struct s_dongle
{
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	t_queue			queue;
	int				is_taken;
	long long		available_at;
}					t_dongle;

typedef struct s_data
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	int				is_edf;
	pthread_mutex_t	print_lock;
	t_dongle		*dongles;
	long long		start_time;
}					t_data;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_data			*table;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	long long		last_compile_start;
	int				nb_compiles;
}					t_coder;


void				*hello(void *arg);
int					main(int argc, char **argv);

int					parsing(int argc, char **argv);
int					check_scheduler(t_data *table, char *scheduler);

int					init_table(t_data *table, int argc, char **argv);
int					init_coders(t_coder **coders, t_data *table);
int					init_queue(t_queue *queue, int max_coders);

void				get_start_time(t_data *table);
long long			get_time(t_data *table);
void				ft_usleep(long long time_in_ms, t_data *table);

void				entry_queue(t_queue *queue, t_request rq);
t_request			pop_prio(t_queue *queue);

#endif
