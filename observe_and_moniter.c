/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observe_and_moniter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:27:16 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/24 11:32:06 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	survived_check(t_thread_memory *info)
{
	int	i;
	int	finish_count;

	if (info->meals_nb > 0)
	{
		i = 0;
		finish_count = 0;
		while (i < info->philo_num)
		{
			pthread_mutex_lock(&(info->meal_lock));
			if (info->philos[i].eat_count >= info->meals_nb)
				finish_count++;
			pthread_mutex_unlock(&(info->meal_lock));
			i++;
		}
		if (finish_count == info->philo_num)
			return (1);
	}
	return (0);
}

int	noteat_check(t_thread_memory *info, t_philo philo, u_int64_t dead_time)
{
	pthread_mutex_lock(&(info->meal_lock));
	if (get_time() - (philo.time_to_die) >= dead_time && philo.eating == 0)
	{
		pthread_mutex_unlock(&(info->meal_lock));
		return (1);
	}
	pthread_mutex_unlock(&(info->meal_lock));
	return (0);
}

int	noteat_dead(t_thread_memory *info)
{
	int	i;

	i = 0;
	while (i < info->philo_num)
	{
		if (noteat_check(info, info->philos[i], info->death_time) == 1)
		{
			protected_output("died", &(info->philos[i]));
			return (1);
		}
		i++;
	}
	return (0);
}

int	death_flag_wake_up(t_thread_memory *info)
{
	if (survived_check(info) == 1)
	{
		pthread_mutex_lock(&(info->dead_lock));
		info->dead = 1;
		pthread_mutex_unlock(&(info->dead_lock));
		return (1);
	}
	if (noteat_dead(info) == 1)
	{
		pthread_mutex_lock(&(info->dead_lock));
		info->dead = 1;
		pthread_mutex_unlock(&(info->dead_lock));
		return (1);
	}
	return (0);
}

void	*moniter(void *thread_info)
{
	t_thread_memory	*info;
	int				dead_flag;

	info = (t_thread_memory *)thread_info;
	dead_flag = 0;
	while (dead_flag != 1)
	{
		if (death_flag_wake_up(info) == 1)
			dead_flag = 1;
	}
	return (NULL);
}
