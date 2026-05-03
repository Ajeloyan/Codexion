/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 02:28:02 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/03 02:12:13 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*hello(void *arg)
{
	int	id;
	t_data *data = (t_data *)arg;

	id = data->id;
	pthread_mutex_lock(data->print_lock);
	printf("Codeur n'%d commence a taffer\n", id);
	pthread_mutex_unlock(data->print_lock);
	usleep(500000);
	pthread_mutex_lock(data->print_lock);
	printf("Codeur n'%d a fini de taffer\n", id);
	pthread_mutex_unlock(data->print_lock);
	return (NULL);
}

int	main(void)
{
	pthread_mutex_t	print_lock;
	t_data			coders[20];
	pthread_t		threads[20];
	int				i;

	pthread_mutex_init(&print_lock, NULL);
	i = 0;
	while (i < 20)
	{
		coders[i].id = i + 1;
		coders[i].print_lock = &print_lock;
		pthread_create(&threads[i], NULL, hello, &coders[i]);
		i++;
	}
	i = 0;
	while (i < 20)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&print_lock);
	return (EXIT_SUCCESS);
}
