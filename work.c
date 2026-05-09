/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 20:07:13 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/09 21:24:14 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void	compiling(t_coder *coder)
{
	pthread_mutex_lock(&coder->table->print_lock);
	printf("%lld %d is compiling\n", get_time(coder->table), coder->id);
	pthread_mutex_unlock(&coder->table->print_lock);
	ft_usleep(coder->table->time_to_compile, coder->table);
}

void	debugging(t_coder *coder)
{
	pthread_mutex_lock(&coder->table->print_lock);
	printf("%lld %d is debugging\n", get_time(coder->table), coder->id);
	pthread_mutex_unlock(&coder->table->print_lock);
	ft_usleep(coder->table->time_to_debug, coder->table);
}

void	refactoring(t_coder *coder)
{
	pthread_mutex_lock(&coder->table->print_lock);
	printf("%lld %d is refactoring\n", get_time(coder->table), coder->id);
	pthread_mutex_unlock(&coder->table->print_lock);
	ft_usleep(coder->table->time_to_refactor, coder->table);
}

void dongle_distrib(t_coder *coder)
{
	if (coder->id % 2 == 0)
		{
			take_dongle(coder, coder->left_dongle);
			take_dongle(coder, coder->right_dongle);
		}
		if (coder->id % 2 != 0)
		{
			take_dongle(coder, coder->right_dongle);
			take_dongle(coder, coder->left_dongle);
		}
}


void	*routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (coder->id % 2 == 0)
		ft_usleep(coder->table->time_to_compile / 10, coder->table);
	while(coder->nb_compiles < coder->table->number_of_compiles_required)
	{
		dongle_distrib(coder);
		if (coder->table->stop_simulation == 1)
			return (NULL);
		coder->last_compile_start = get_time(coder->table);
		compiling(coder);
		release_dongle(coder, coder->left_dongle);
		release_dongle(coder, coder->right_dongle);
		debugging(coder);
		refactoring(coder);
		coder->nb_compiles++;
	}
	return (NULL);
}
