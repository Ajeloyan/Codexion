/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 20:07:13 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/04 01:51:52 by ajeloyan         ###   ########.fr       */
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

	id = coder->id;
	pthread_mutex_lock(coder->table->print_lock);
	printf("Codeur n'%d commence a taffer\n", id);
	pthread_mutex_unlock(coder->table->print_lock);
	usleep(500000);
	pthread_mutex_lock(coder->table->print_lock);
	printf("Codeur n'%d a fini de taffer\n", id);
	pthread_mutex_unlock(coder->table->print_lock);
	return (NULL);
}