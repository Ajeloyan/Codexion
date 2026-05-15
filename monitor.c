/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 21:25:03 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/15 20:02:28 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <stdio.h>
#include <unistd.h>

void	check_coders(t_coder *coder, t_data *table)
{
	int	i;
	int	coders_done;

	i = 0;
	coders_done = 0;
	while (i < table->number_of_coders)
	{
		pthread_mutex_lock(&table->state_lock);
		if (coder[i].nb_compiles >= table->number_of_compiles_required)
			coders_done++;
		else if (get_time(table)
			- coder[i].last_compile_start >= table->time_to_burnout)
		{
			pthread_mutex_lock(&table->print_lock);
			printf("%lld %d burned out\n", get_time(table), coder[i].id);
			pthread_mutex_unlock(&table->print_lock);
			table->stop_simulation = 1;
			pthread_mutex_unlock(&table->state_lock);
			return ;
		}
		pthread_mutex_unlock(&table->state_lock);
		i++;
	}
	if (coders_done == table->number_of_coders)
		table->stop_simulation = 1;
}

void	wake_up(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_coders)
	{
		pthread_mutex_lock(&table->dongles[i].lock);
		pthread_cond_broadcast(&table->dongles[i].cond);
		pthread_mutex_unlock(&table->dongles[i].lock);
		i++;
	}
}

void	monitor_routine(t_coder *coder, t_data *table)
{
	while (table->stop_simulation != 1)
	{
		check_coders(coder, table);
		usleep(1000);
	}
	wake_up(table);
}
