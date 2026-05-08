/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 22:42:16 by armenag           #+#    #+#             */
/*   Updated: 2026/05/09 00:22:05 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"

void take_dongle(t_coder *coder, t_dongle *dongle)
{
    t_request rq;
    long long current_time;
    long long time_to_wait;
    
    rq = create_request(coder);
    pthread_mutex_lock(&dongle->lock);
    entry_queue(&dongle->queue, rq);
    while(dongle->is_taken == 1 || coder->id != dongle->queue.request[0].coder_id)
    {
        pthread_cond_wait(&dongle->cond, &dongle->lock);
    }
    rq = pop_prio(&dongle->queue);
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