/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:07:20 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/26 15:54:13 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_fork_init(t_thread_memory *thread_m)
{
	int	i;

	i = 0;
	while (i < thread_m->philo_num)
	{
		if (pthread_mutex_init(&thread_m->forks[i], NULL) != 0)
		{
			init_fork_mutex_error(thread_m, i);
			return (1);
		}
		i++;
	}
	return (0);
}
