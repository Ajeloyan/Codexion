/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:28:02 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/06 20:24:10 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
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
			pthread_mutex_destroy(&table->dongles[i]);
			i++;
		}
		free(table->dongles);	
	}
	i = 0;
	pthread_mutex_destroy(&table->print_lock);
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
	join_threads(&table, &coders);
	cleanup(&table, coders);
	return (0);
}