/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:07:46 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/29 12:46:56 by dhosokaw         ###   ########.fr       */
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
	ft_strict_usleep(calc_wait_time(philo));
	printf("now_wake_up pihlo:%i\n",philo->id);
	while (dead_check(philo->data) != 1)
	{
		philo_dinner(philo);
		philo_sleep(philo);
		philo_think_start(philo);
	}
	return (NULL);
}

int	thread_error(t_thread_memory *thread_info)
{
	all_mutex_destroy(thread_info);
	memory_free(thread_info);
	return (1);
}

int	thread_make_and_do(t_thread_memory *thread_info, void *func)
{
	int			i;
	pthread_t	moniter_th;

	if (pthread_create(&(moniter_th), NULL, moniter, thread_info) != 0)
		return (1);
	i = 0;
	while (i < thread_info->philo_num)
	{
		if (pthread_create(&(thread_info->tid[i]), NULL, func,
				(void *)(&thread_info->philos[i])) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < thread_info->philo_num)
	{
		if (pthread_join(thread_info->tid[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_join(moniter_th, NULL) != 0)
		return (1);
	all_mutex_destroy(thread_info);
	memory_free(thread_info);
	return (0);
}

int	main(int argc, char **argv)
{
	t_thread_memory	thread_info;

	if (check_validation_arg(argc, argv) == 1)
		return (1);
	if (thread_init(&thread_info, argv) == 1)
		return (1);
	philo_init(&thread_info);
	if (thread_make_and_do(&thread_info, philo_ploblem) == 1)
		return (thread_error(&thread_info));
	return (0);
}
