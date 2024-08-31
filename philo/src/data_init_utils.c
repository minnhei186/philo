/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:07:20 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/31 12:27:17 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_arg_init(t_thread_memory *thread_m, char **argv)
{
	thread_m->philo_num = ft_atoi(argv[1]);
	thread_m->death_time = ft_atoi(argv[2]);
	thread_m->eat_time = ft_atoi(argv[3]);
	thread_m->sleep_time = ft_atoi(argv[4]);
	if (argv[5])
		thread_m->meals_nb = ft_atoi(argv[5]);
	else
		thread_m->meals_nb = 0;
}

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
