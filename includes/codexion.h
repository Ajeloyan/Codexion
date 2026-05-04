/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 01:50:57 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/04 02:06:24 by ajeloyan         ###   ########.fr       */
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
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dongles;
}					t_data;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_data			*table;
	pthread_mutex_t	*left_dongle;
	pthread_mutex_t *right_dongle;
}					t_coder;

void				*hello(void *arg);
int					main(int argc, char **argv);

t_data				*parsing(int argc, char **argv);

int					ft_is_digit(char c);

#endif
