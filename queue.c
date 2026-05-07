/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 02:19:22 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/07 02:28:20 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"


void entry_queue(t_queue *queue, t_request *rq, int score)
{
    int current 
    if (queue->size >= queue->capacity)
        return;
    queue[queue->size] = &rq;
    queue->size++;
    while(rq->timestamp)
}