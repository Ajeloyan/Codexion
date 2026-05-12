/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 00:42:42 by armenag           #+#    #+#             */
/*   Updated: 2026/05/13 01:19:04 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "includes/codexion.h"
#include <unistd.h>

int get_start_time(t_data *table)
{
    struct timeval tv;
    long long start_time;
    
    if (gettimeofday(&tv, NULL) == -1)
        return(print_error("gettimeofday failed on start"));
    start_time = (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    table->start_time = start_time;
    return (0);
}

long long get_time(t_data *table)
{
    struct timeval tv;
    long long current_time;

    if (gettimeofday(&tv, NULL) == -1)
    {
        print_error("gettimeofday failed");
        pthread_mutex_lock(&table->state_lock);
        table->stop_simulation = 1;
        pthread_mutex_unlock(&table->state_lock);
        return (0);
    }
    current_time = (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    return (current_time - table->start_time);
}

void ft_usleep(long long time_in_ms, t_data *table)
{
    long long start;

    start = get_time(table);
    while ((get_time(table) - start) < time_in_ms)
    {
        pthread_mutex_lock(&table->state_lock);
        if (table->stop_simulation == 1)
        {
            pthread_mutex_unlock(&table->state_lock);
            break;
        }
        pthread_mutex_unlock(&table->state_lock);
        usleep(500);
    }
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int print_error(char *str)
{
    write(2, "Error\n", 6);
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    return (1);
}