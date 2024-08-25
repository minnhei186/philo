/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:08:38 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/24 11:52:30 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_mutex_init(t_thread_memory *thread_m)
{
	int	i;

	i = 0;
	while (i < thread_m->philo_num)
	{
		if (pthread_mutex_init(&thread_m->forks[i], NULL) != 0)
			error_exit("error: failed init mutex");
		i++;
	}
	if (pthread_mutex_init(&thread_m->dead_lock, NULL) != 0)
		error_exit("error: failed init mutex");
	if (pthread_mutex_init(&thread_m->meal_lock, NULL) != 0)
		error_exit("error: failed init mutex");

	if (pthread_mutex_init(&thread_m->write, NULL) != 0)
		error_exit("error: failed init mutex");
}

void	thread_init(t_thread_memory *thread_m, char **argv)
{
	thread_m->philo_num = atoi(argv[1]);
	thread_m->death_time = atoi(argv[2]);
	thread_m->eat_time = atoi(argv[3]);
	thread_m->sleep_time = atoi(argv[4]);
	if(argv[5])
		thread_m->meals_nb = atoi(argv[5]);
	else
		thread_m->meals_nb=0;
	thread_m->start_time = get_time();
	thread_m->tid = (pthread_t *)malloc(sizeof(pthread_t)
			* (thread_m->philo_num));
	if (!thread_m->tid)
		error_exit("error:malloc");
	thread_m->philos = (t_philo *)malloc(sizeof(t_philo)
			* (thread_m->philo_num));
	if (!thread_m->philos)
		error_exit("error:malloc");
	thread_m->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (thread_m->philo_num));
	if (!thread_m->forks)
		error_exit("error:malloc");
	thread_mutex_init(thread_m);
}

void	philo_data_init(t_thread_memory *thread_m, t_philo *philo, int philo_id)
{
	philo->data = thread_m;
	philo->id = philo_id;
	philo->eat_count = 0;
	philo->eating = 0;
	philo->time_to_die = get_time();
	philo->t1 = thread_m->tid[philo_id];
}

void	philo_mutex_init(t_thread_memory *thread_m, t_philo *philo)
{
	int	current_id;
	int	philo_n;

	philo_n = thread_m->philo_num;
	current_id = philo->id;
	philo->l_fork = &(thread_m->forks[current_id]);
	if (current_id == 0)
		philo->r_fork = &(thread_m->forks[philo_n - 1]);
	else
		philo->r_fork = &(thread_m->forks[current_id -1]);
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
