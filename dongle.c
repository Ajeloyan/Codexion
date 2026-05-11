/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 22:42:16 by armenag           #+#    #+#             */
/*   Updated: 2026/05/11 20:59:03 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <stdio.h>

void take_dongle(t_coder *coder, t_dongle *dongle)
{
    t_request rq;
    long long current_time;
    long long time_to_wait;
    
    rq = create_request(coder);
    pthread_mutex_lock(&dongle->lock);
    entry_queue(&dongle->queue, rq);
    while(dongle->is_taken == 1 || coder->id != dongle->queue.request[0].coder_id)
        pthread_cond_wait(&dongle->cond, &dongle->lock);
    rq = pop_prio(&dongle->queue);
    pthread_mutex_lock(&coder->table->state_lock);
    pthread_mutex_lock(&coder->table->print_lock);
    if (coder->table->stop_simulation == 1)
    {
        pthread_mutex_unlock(&coder->table->print_lock);
        pthread_mutex_unlock(&coder->table->state_lock);
        pthread_mutex_unlock(&dongle->lock);
        return;
    }
    printf("%lld %d has taken a dongle\n", get_time(coder->table), coder->id);
    pthread_mutex_unlock(&coder->table->print_lock);
    pthread_mutex_unlock(&coder->table->state_lock);
    dongle->is_taken = 1;
    current_time = get_time(coder->table);
    time_to_wait = dongle->available_at - current_time;
    pthread_mutex_unlock(&dongle->lock);
    if (time_to_wait > 0)
        ft_usleep(time_to_wait, coder->table);
}

void release_dongle(t_coder *coder, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->lock);
    dongle->is_taken = 0;
    dongle->available_at = get_time(coder->table) + coder->table->dongle_cooldown;
    pthread_cond_broadcast(&dongle->cond);
    pthread_mutex_unlock(&dongle->lock);
}