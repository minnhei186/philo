/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:22:42 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/26 15:53:34 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think_start(t_philo *philo)
{
	protected_output("is thinking\n", philo);
}

void	philo_sleep(t_philo *philo)
{
	protected_output("is sleeping\n", philo);
	ft_strict_usleep(philo->data->sleep_time);
}

void	get_fork(char *fork, t_philo *philo)
{
	if (ft_strncmp("left", fork, 4) == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		protected_output("has taken a fork\n", philo);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		protected_output("has taken a fork\n", philo);
	}
}

void	eat(t_philo *philo)
{
	philo->eating = 1;
	protected_output("is eating\n", philo);
	pthread_mutex_lock(&(philo->data->meal_lock));
	philo->time_to_die = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->data->meal_lock));
	ft_strict_usleep(philo->data->eat_time);
	philo->eating = 0;
}

void	philo_dinner(t_philo *philo)
{
	get_fork("left", philo);
	if (philo->data->philo_num == 1)
	{
		ft_strict_usleep(philo->data->death_time);
		pthread_mutex_unlock(philo->l_fork);
	}
	get_fork("right", philo);
	eat(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
