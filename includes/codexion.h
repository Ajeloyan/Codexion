/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajeloyan <ajeloyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 01:50:57 by ajeloyan          #+#    #+#             */
/*   Updated: 2026/05/03 02:09:30 by ajeloyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

typedef struct s_data
{
	int				id;
	pthread_mutex_t	*print_lock;
}					t_data;

void				*hello(void *arg);
int					main(void);

#endif
