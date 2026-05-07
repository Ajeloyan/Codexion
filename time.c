/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 02:11:43 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/07 02:13:31 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "includes/codexion.h"

void get_start_time(t_data *table)
{
    struct timeval tv;
    long start_time;
    
    gettimeofday(&tv, NULL);
    start_time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    table->start_time = start_time;
}