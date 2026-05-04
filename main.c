/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:28:02 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/04 02:13:06 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data			*table;
	pthread_mutex_t	print_lock;
	t_coder			*coders;
	int				i;

	i = 0;
	if (argc != 2)
		return (1);
	table = parsing(argc, argv);
	table->dongles = malloc(sizeof(pthread_mutex_t) * table->number_of_coders);
	while(i < table->number_of_coders)
	{
		table->dongles = 
	}
	if (!table->dongles)
		return (1);
	if (table->number_of_coders == -1)
		return (1);
	else
	{
		coders = malloc(sizeof(t_coder) * table->number_of_coders);
		if (!coders)
			return (1);
	}
	pthread_mutex_init(&print_lock, NULL);
	table->print_lock = &print_lock;
	while (i < table->number_of_coders)
	{
		coders[i].id = i + 1;
		coders[i].table = table;
		coders[i].left_dongle = &table->dongles[i];
		coders[i].right_dongle = &table->dongles[i + 1] % table->number_of_coders;
		pthread_create(&coders[i].thread, NULL, hello, &coders[i]);
		i++;
	}
	i = 0;
	while (i < table->number_of_coders)
	{
		pthread_join(coders[i].thread, NULL);
		i++;
	}    
	pthread_mutex_destroy(&print_lock);
	free(coders);
	free(table);
	return (EXIT_SUCCESS);
}
