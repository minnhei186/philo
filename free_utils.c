/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:07:20 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/24 12:48:10 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//エラーが発生した（exitがしよう出来ないことを考えておこう)NULL,,,

void	mutex_free(t_thread_memory *thread_info)
{
	int	i;

	pthread_mutex_destroy(&(thread_info->dead_lock));
	pthread_mutex_destroy(&(thread_info->meal_lock));
	pthread_mutex_destroy(&(thread_info->write));
	i = 0;
	while (i < thread_info->philo_num)
	{
		pthread_mutex_destroy(thread_info->forks);
		i++;
	}
}

//ポインタ空間だけをfreeしている。こういうこっちゃ、全く異なる。
//世界があるよ。
void	memory_free(t_thread_memory *thread_info)
{
	if (thread_info->tid)
		free(thread_info->tid);
	if (thread_info->philos)
		free(thread_info->philos);
	if (thread_info->forks)
		free(thread_info->forks);
}
