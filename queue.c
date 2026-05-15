/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 02:19:22 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/15 20:23:57 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"

int	is_better_prio(t_request r1, t_request r2)
{
	if (r1.score < r2.score)
		return (1);
	if (r1.score == r2.score && r1.coder_id < r2.coder_id)
		return (1);
	return (0);
}

void	entry_queue(t_queue *queue, t_request rq)
{
	int	current_idx;
	int	parent_idx;

	if (queue->size >= queue->capacity)
		return ;
	current_idx = queue->size;
	queue->request[current_idx] = rq;
	queue->size++;
	parent_idx = (current_idx - 1) / 2;
	while (current_idx > 0 && is_better_prio(queue->request[current_idx],
			queue->request[parent_idx]))
	{
		swap_request(queue, current_idx, parent_idx);
		current_idx = parent_idx;
		parent_idx = (current_idx - 1) / 2;
	}
}

void	bubble_down(t_queue *queue, int current_idx)
{
	int	child1_idx;
	int	child2_idx;
	int	smallest_idx;

	while ((current_idx * 2) + 1 < queue->size)
	{
		child1_idx = (current_idx * 2) + 1;
		child2_idx = (current_idx * 2) + 2;
		smallest_idx = child1_idx;
		if (child2_idx < queue->size
			&& is_better_prio(queue->request[child2_idx],
				queue->request[child1_idx]))
			smallest_idx = child2_idx;
		if (is_better_prio(queue->request[current_idx],
				queue->request[smallest_idx]))
			break ;
		swap_request(queue, current_idx, smallest_idx);
		current_idx = smallest_idx;
	}
}

t_request	pop_prio(t_queue *queue)
{
	t_request	winner;

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
