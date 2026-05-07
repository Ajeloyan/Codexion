/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 20:07:13 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/06 22:25:54 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void	*hello(void *arg)
{
	int i;
	int	id;
	t_coder *coder = (t_coder *)arg;

	i = 0;
	while (i < coder->table->number_of_compiles_required)
	{
		id = coder->id;
		pthread_mutex_lock(&coder->table->print_lock);
		printf("%ld %d is compiling\n", get_time(coder->table), id);
		pthread_mutex_unlock(&coder->table->print_lock);
		usleep((coder->table->time_to_compile) * 1000);
		pthread_mutex_lock(&coder->table->print_lock);
		printf("%ld %d is debugging\n", get_time(coder->table), id);
		pthread_mutex_unlock(&coder->table->print_lock);
		usleep((coder->table->time_to_debug) * 1000);
		pthread_mutex_lock(&coder->table->print_lock);
		printf("%ld %d is refactoring\n", get_time(coder->table), id);
		pthread_mutex_unlock(&coder->table->print_lock);
		usleep((coder->table->time_to_refactor) * 1000);
		i++;
	}
	return (NULL);
}