/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 02:09:00 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/15 20:01:48 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <pthread.h>
#include <stdlib.h>

int	init_coders(t_coder **coders, t_data *table)
{
	int	i;

	i = 0;
	*coders = malloc(sizeof(t_coder) * table->number_of_coders);
	if (!(*coders))
		return (print_error("Memory allocation failed for coders"));
	while (i < table->number_of_coders)
	{
		(*coders)[i].id = i + 1;
		(*coders)[i].table = table;
		(*coders)[i].left_dongle = &table->dongles[i];
		(*coders)[i].right_dongle = &table->dongles[(i + 1)
			% table->number_of_coders];
		(*coders)[i].nb_compiles = 0;
		i++;
	}
	return (0);
}

int	init_dongles(t_data *table)
{
	int	i;

	i = 0;
	table->dongles = malloc(sizeof(t_dongle) * table->number_of_coders);
	if (!table->dongles)
		return (1);
	while (i < table->number_of_coders)
	{
		if (pthread_mutex_init(&table->dongles[i].lock, NULL) != 0)
			return (print_error("Mutex initialization failed"));
		if (pthread_cond_init(&table->dongles[i].cond, NULL) != 0)
			return (print_error("Condition variable initialization failed"));
		if (init_queue(&table->dongles[i].queue, table->number_of_coders))
			return (1);
		table->dongles[i].is_taken = 0;
		table->dongles[i].available_at = 0;
		i++;
	}
	return (0);
}

int	init_table(t_data *table, int argc, char **argv)
{
	if (parsing(argc, argv) != 0)
		return (1);
	table->number_of_coders = atoi(argv[1]);
	if (table->number_of_coders <= 0)
		return (print_error("number_of_coders must be greater than 0"));
	table->time_to_burnout = atoi(argv[2]);
	table->time_to_compile = atoi(argv[3]);
	table->time_to_debug = atoi(argv[4]);
	table->time_to_refactor = atoi(argv[5]);
	table->number_of_compiles_required = atoi(argv[6]);
	if (table->number_of_compiles_required <= 0)
		return (print_error("nb_compiles_required must be > 0"));
	table->dongle_cooldown = atoi(argv[7]);
	if (check_scheduler(table, argv[8]) != 0)
		return (1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (print_error("Print_lock variable initialization failed"));
	if (init_dongles(table) != 0)
		return (1);
	if (pthread_mutex_init(&table->state_lock, NULL) != 0)
		return (print_error("State_lock variable initialization failed"));
	table->stop_simulation = 0;
	return (0);
}

int	init_queue(t_queue *queue, int max_coders)
{
	queue->request = malloc(sizeof(t_request) * max_coders);
	if (!queue->request)
		return (1);
	queue->size = 0;
	queue->capacity = max_coders;
	return (0);
}
