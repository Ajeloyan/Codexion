/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 21:25:03 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/09 22:35:43 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"

void monitor_routine(t_coder *monitor, t_coder *coder, t_data *table)
{
    int coders_done;
    int i;

    i = 0;
    coders_done = 0;
    while (table->stop_simulation != 1)
    {
        while (i < table->number_of_coders)
        {
            pthread_mutex_lock(&table->state_lock);
            if (get_time(table) - coder[i].last_compile_start >= table->time_to_burnout)
            {
                pthread_mutex_lock(&table->print_lock);
                printf("%lld %d burned out\n", get_time(coder->table), coder->id);
                pthread_mutex_unlock(&table->print_lock);
                table->stop_simulation = 1;
            }
            pthread_mutex_unlock(&table->state_lock);
            i++;
        }
    }
}