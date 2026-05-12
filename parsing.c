/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armenag <armenag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 16:20:57 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/13 01:06:35 by armenag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int	int_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_scheduler(t_data *table, char *scheduler)
{
	if (strcmp(scheduler, "fifo") == 0)
		table->is_edf = 0;
	else if (strcmp(scheduler, "edf") == 0)
		table->is_edf = 1;
	else
		return (print_error("'fifo' or 'edf' expected"));
	return (0);
}

int	parsing(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 9)
		return (print_error("Invalid number of arguments"));
	while (i < argc - 1)
	{
		if (int_checker(argv[i]) == 1)
			return (print_error("Int expected"));
		i++;
	}
	return (0);
}
