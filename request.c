/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:18:53 by armenag           #+#    #+#             */
/*   Updated: 2026/05/08 17:21:29 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"

void swap_request(t_queue *queue, int current, int parent)
{
    t_request temp;
    
    temp = queue->request[parent];
    queue->request[parent] = queue->request[current];
    queue->request[current] = temp;
}

t_request create_request(t_coder *coder)
{
    t_request rq;

    rq.coder_id = coder->id;
    if (coder->table->is_edf == 0)
        rq.score = get_time(coder->table);
    else
        rq.score = coder->last_compile_start + coder->table->time_to_burnout;
    return rq;
}