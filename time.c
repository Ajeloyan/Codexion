/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 02:11:43 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/08 16:54:48 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "includes/codexion.h"
#include <unistd.h>

void get_start_time(t_data *table)
{
    struct timeval tv;
    long long start_time;
    
    gettimeofday(&tv, NULL);
    start_time = (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    table->start_time = start_time;
}

long long get_time(t_data *table)
{
    struct timeval tv;
    long long current_time;

    gettimeofday(&tv, NULL);
    current_time = (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    return (current_time - table->start_time);
}

void ft_usleep(long long time_in_ms, t_data *table)
{
    long long start;

    start = get_time(table);
    while ((get_time(table) - start) < time_in_ms)
    {
        usleep(500);
    }
}