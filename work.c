/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 20:07:13 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/08 22:39:12 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void	*hello(void *arg)
{
	int	id;
	t_coder *coder = (t_coder *)arg;

	while (coder->nb_compiles < coder->table->number_of_compiles_required)
	{
		id = coder->id;
		pthread_mutex_lock(&coder->table->print_lock);
		printf("%lld %d is compiling\n", get_time(coder->table), id);
		pthread_mutex_unlock(&coder->table->print_lock);
		ft_usleep((coder->table->time_to_compile), coder->table);
		pthread_mutex_lock(&coder->table->print_lock);
		printf("%lld %d is debugging\n", get_time(coder->table), id);
		pthread_mutex_unlock(&coder->table->print_lock);
		ft_usleep((coder->table->time_to_debug), coder->table);
		pthread_mutex_lock(&coder->table->print_lock);
		printf("%lld %d is refactoring\n", get_time(coder->table), id);
		pthread_mutex_unlock(&coder->table->print_lock);
		ft_usleep((coder->table->time_to_refactor), coder->table);
		coder->nb_compiles++;
	}
	return (NULL);
}