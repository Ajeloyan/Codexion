/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 22:31:44 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/15 21:15:48 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <stdio.h>

void	compiling(t_coder *coder)
{
	print_action(coder, "is compiling");
	ft_usleep(coder->table->time_to_compile, coder->table);
}

void	debugging(t_coder *coder)
{
	print_action(coder, "is debugging");
	ft_usleep(coder->table->time_to_debug, coder->table);
}

void	refactoring(t_coder *coder)
{
	print_action(coder, "is refactoring");
	ft_usleep(coder->table->time_to_refactor, coder->table);
}

void	print_action(t_coder *coder, char *action)
{
	pthread_mutex_lock(&coder->table->state_lock);
	pthread_mutex_lock(&coder->table->print_lock);
	if (coder->table->stop_simulation == 1)
	{
		pthread_mutex_unlock(&coder->table->print_lock);
		pthread_mutex_unlock(&coder->table->state_lock);
		return ;
	}
	printf("%lld %d %s\n", get_time(coder->table), coder->id, action);
	pthread_mutex_unlock(&coder->table->print_lock);
	pthread_mutex_unlock(&coder->table->state_lock);
}
