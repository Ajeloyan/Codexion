/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 21:25:03 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/13 00:34:41 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <stdio.h>
#include <unistd.h>

void monitor_routine(t_coder *coder, t_data *table)
{
    int coders_done;
    int i;

    while (table->stop_simulation != 1)
    {
        coders_done = 0;
        i = 0;
        while (i < table->number_of_coders)
        {
            pthread_mutex_lock(&table->state_lock);
            if (get_time(table) - coder[i].last_compile_start >= table->time_to_burnout)
            {
                pthread_mutex_lock(&table->print_lock);
                printf("%lld %d burned out\n", get_time(coder->table), coder[i].id);
                pthread_mutex_unlock(&table->print_lock);
                table->stop_simulation = 1;
                pthread_mutex_unlock(&table->state_lock);
                break;
            }
            if (coder[i].nb_compiles >= coder->table->number_of_compiles_required)
                coders_done++;
            pthread_mutex_unlock(&table->state_lock);
            i++;
        }
        if (coders_done == coder->table->number_of_coders)
            table->stop_simulation = 1;
        usleep(1000);
    }
    i = 0;
    while(i < table->number_of_coders)
    {
        pthread_mutex_lock(&table->dongles[i].lock);
        pthread_cond_broadcast(&table->dongles[i].cond);
        pthread_mutex_unlock(&table->dongles[i].lock);
        i++;
    }
    return;
}