/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 16:20:57 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/03 22:41:13 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/codexion.h"
#include <stdio.h>
#include <stdlib.h>

int	int_checker(char *str)
{
    int int_value;
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_is_digit(str[i]) != 0)
			return (-1);
		i++;
	}
	int_value = atoi(str);
    if (int_value <= 0)
        return (-1);
    return (int_value);
}


t_data *parsing(int argc, char **argv)
{
    t_data *table;

    (void)argc;
    // if (argc != 9)
    //     return (NULL);
    table = malloc(sizeof(t_data));
    if (!table)
    {
        free(table);
        return (NULL);
    }
    table->number_of_coders = int_checker(argv[1]);
    // table->time_to_burnout = int_checker(argv[2]);
    // table->time_to_compile = int_checker(argv[3]);
    // table->time_to_debug = int_checker(argv[4]);
    // table->time_to_refactor = int_checker(argv[5]);
    // table->number_of_compiles_required = int_checker(argv[6]);
    // table->dongle_cooldown = int_checker(argv[7]);
    // table->scheduler = "bonjour";
    return (table);
}