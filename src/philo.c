/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:07:46 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/26 15:51:37 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_thread_memory *info)
{
	pthread_mutex_lock(&(info->dead_lock));
	if (info->dead == 1)
	{
		pthread_mutex_unlock(&(info->dead_lock));
		return (1);
	}
	pthread_mutex_unlock(&(info->dead_lock));
	return (0);
}

void	*philo_ploblem(void *some_philo)
{
	t_philo	*philo;

	philo = (t_philo *)some_philo;
	if (philo->id % 2 == 1)
		ft_strict_usleep(philo->data->eat_time / 2);
	while (dead_check(philo->data) != 1)
	{
		philo_dinner(philo);
		philo_sleep(philo);
		philo_think_start(philo);
	}
	return (NULL);
}

void	thread_make_and_do(t_thread_memory *thread_info, void *func)
{
	int			i;
	pthread_t	moniter_th;

	pthread_create(&(moniter_th), NULL, moniter, thread_info);
	i = 0;
	while (i < thread_info->philo_num)
	{
		pthread_create(&(thread_info->tid[i]), NULL, func,
			(void *)(&thread_info->philos[i]));
		i++;
	}
	i = 0;
	while (i < thread_info->philo_num)
	{
		pthread_join(thread_info->tid[i], NULL);
		i++;
	}
	pthread_join(moniter_th, NULL);
	all_mutex_destroy(thread_info);
	memory_free(thread_info);
}

int	main(int argc, char **argv)
{
	t_thread_memory	thread_info;

	if (check_validation_arg(argc, argv) == 1)
		return (1);
	if (thread_init(&thread_info, argv) == 1)
		return (1);
	philo_init(&thread_info);
	thread_make_and_do(&thread_info, philo_ploblem);
	return (0);
}
