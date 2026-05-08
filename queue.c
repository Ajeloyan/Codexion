/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 02:19:22 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/08 17:18:51 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"

void entry_queue(t_queue *queue, t_request rq)
{
    int current_idx;
    int parent_idx;

    if (queue->size >= queue->capacity)
        return;
    current_idx = queue->size;
    queue->request[current_idx] = rq;
    queue->size++;
    
    parent_idx = (current_idx - 1) / 2;

    while (current_idx > 0 && queue->request[parent_idx].score > queue->request[current_idx].score)
    {
        swap_request(queue, current_idx, parent_idx);

        current_idx = parent_idx;
        parent_idx = (current_idx - 1) / 2;
    }
}

void bubble_down(t_queue *queue, int current_idx)
{
    int child1_idx;
    int child2_idx;
    int smallest_idx;

    while ((current_idx * 2) + 1 < queue->size)
    {
        child1_idx = (current_idx * 2) + 1;
        child2_idx = (current_idx * 2) + 2;
        smallest_idx = child1_idx;
        if (child2_idx < queue->size && queue->request[child2_idx].score < queue->request[child1_idx].score)
            smallest_idx = child2_idx;
        if (queue->request[current_idx].score <= queue->request[smallest_idx].score)
            break;
        swap_request(queue, current_idx, smallest_idx);
        current_idx = smallest_idx;
    }
}

t_request pop_prio(t_queue *queue)
{
    t_request winner;
    
    if (queue->size <= 0)
    {
        winner.coder_id = -1;
        return (winner);
    }
    winner = queue->request[0];
    queue->request[0] = queue->request[queue->size - 1];
    queue->size--;
    bubble_down(queue, 0);
    return (winner);
}
