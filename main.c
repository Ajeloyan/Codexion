/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:28:02 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/13 00:29:04 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void cleanup(t_data *table, t_coder *coders)
{
	int i;

	i = 0;
	if (table->dongles)
	{
		while (i < table->number_of_coders)
		{
			pthread_mutex_destroy(&table->dongles[i].lock);
			pthread_cond_destroy(&table->dongles[i].cond);
			if (table->dongles[i].queue.request)
				free(table->dongles[i].queue.request);
			i++;
		}
		free(table->dongles);
	}
	i = 0;
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->state_lock);
	if (coders)
		free(coders);
}

int join_threads(t_data *table, t_coder **coders)
{
	int i;

	i = 0;
	while (i < table->number_of_coders)
	{
		pthread_join((*coders)[i].thread, NULL);
		i++;
	}
	return (0);
}

int start_simulation(t_data *table, t_coder *coders)
{
	int i;
	
	i = 0;
	get_start_time(table);
	while (i < table->number_of_coders)
	{
		coders[i].last_compile_start = get_time(table);
		// if (pthread_create(&monitor.thread))
		if (pthread_create(&coders[i].thread, NULL, routine, &coders[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_coder *coders;
	t_data table;

	if (init_table(&table, argc, argv) != 0)
		return (1);
	if (init_coders(&coders, &table) != 0)
	{
		cleanup(&table, coders);
		return (1);
	}
	if (start_simulation(&table, coders) != 0)
	{
		cleanup(&table, coders);
		return(1);
	}
	monitor_routine(coders, &table);
	join_threads(&table, &coders);
	cleanup(&table, coders);
	return (0);
}