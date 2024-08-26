/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:05:57 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/26 15:52:25 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork_mutex_error(t_thread_memory *info, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&(info->forks[j]));
		j++;
	}
	return ;
}

void	init_mutex_error(pthread_mutex_t *dead_lock, pthread_mutex_t *meal_lock,
		pthread_mutex_t *write)
{
	if (dead_lock)
		pthread_mutex_destroy(dead_lock);
	if (meal_lock)
		pthread_mutex_destroy(meal_lock);
	if (write)
		pthread_mutex_destroy(write);
}

int	error_exit(t_thread_memory *info, char *str)
{
	printf("%s\n", str);
	memory_free(info);
	return (1);
}
