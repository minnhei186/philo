/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:08:38 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/31 12:27:37 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_mutex_init(t_thread_memory *thread_m)
{
	if (pthread_mutex_init(&thread_m->dead_lock, NULL) != 0)
	{
		init_mutex_error(NULL, NULL, NULL);
		return (1);
	}
	if (pthread_mutex_init(&thread_m->meal_lock, NULL) != 0)
	{
		init_mutex_error(&(thread_m->dead_lock), NULL, NULL);
		return (1);
	}
	if (pthread_mutex_init(&thread_m->write, NULL) != 0)
	{
		init_mutex_error(&(thread_m->dead_lock), &(thread_m->meal_lock), NULL);
		return (1);
	}
	if (thread_fork_init(thread_m) != 0)
	{
		init_mutex_error(&(thread_m->dead_lock), &(thread_m->meal_lock),
			&(thread_m->write));
		return (1);
	}
	return (0);
}

int	thread_init(t_thread_memory *thread_m, char **argv)
{
	thread_arg_init(thread_m, argv);
	thread_m->start_time = get_time();
	if (thread_m->start_time == 0)
		return (1);
	thread_m->tid = (pthread_t *)malloc(sizeof(pthread_t)
			* (thread_m->philo_num));
	if (!thread_m->tid)
		return (error_exit(thread_m, "error:malloc"));
	thread_m->philos = (t_philo *)malloc(sizeof(t_philo)
			* (thread_m->philo_num));
	if (!thread_m->philos)
		return (error_exit(thread_m, "error:malloc"));
	thread_m->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (thread_m->philo_num));
	if (!thread_m->forks)
		return (error_exit(thread_m, "error:malloc"));
	if (thread_mutex_init(thread_m) == 1)
		return (error_exit(thread_m, "error:mutex"));
	return (0);
}

void	philo_data_init(t_thread_memory *thread_m, t_philo *philo, int philo_id)
{
	philo->data = thread_m;
	philo->id = philo_id + 1;
	philo->eat_count = 0;
	philo->time_to_die = thread_m->start_time;
}

void	philo_mutex_init(t_thread_memory *thread_m, t_philo *philo)
{
	int	current_id;
	int	philo_n;

	philo_n = thread_m->philo_num;
	current_id = philo->id;
	philo->l_fork = &(thread_m->forks[current_id - 1]);
	if (current_id == 1)
		philo->r_fork = &(thread_m->forks[philo_n - 1]);
	else
		philo->r_fork = &(thread_m->forks[current_id - 2]);
}

void	philo_init(t_thread_memory *thread_m)
{
	int	i;

	i = 0;
	while (i < thread_m->philo_num)
	{
		philo_data_init(thread_m, &thread_m->philos[i], i);
		philo_mutex_init(thread_m, &thread_m->philos[i]);
		i++;
	}
}
