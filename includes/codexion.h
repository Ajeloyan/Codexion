/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 01:50:57 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/07 02:13:08 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

typedef struct s_data
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*dongles;
	long			start_time;
}					t_data;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_data			*table;
	pthread_mutex_t	*left_dongle;
	pthread_mutex_t	*right_dongle;
}					t_coder;

typedef struct s_request
{
	int				coder_id;
	long long		timestamp;
}					t_request;

typedef struct s_queue
{
	t_request		request;
	int				size;
	int				capacity;
}					t_queue;

void				*hello(void *arg);
int					main(int argc, char **argv);

int					parsing(int argc, char **argv);
int					check_scheduler(t_data *table, char *scheduler);

int					init_table(t_data *table, int argc, char **argv);
int					init_coders(t_coder **coders, t_data *table);

void				get_start_time(t_data *table);
long				get_time(t_data *table);

#endif
