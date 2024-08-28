/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:07:46 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/28 13:44:13 by dhosokaw         ###   ########.fr       */
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

//static int calc_meal_time(t_philo *philo)
//{
//	int n;
//	int id;
//	int k;
//	int unit;
//
//	n=philo->data->philo_num;
//	if(n==1)
//		return philo->data->start_time;
//	id=philo->id;
//	k=n/2;
//	unit=(philo->data->eat_time)/k;
//	if(unit==0)
//		unit=1;
//	return (philo->data->start_time+unit(id*k)%n)
//
//}

static int calc_meal_time(t_philo *philo)
{
    int n;
    int id;
    int k;
    int unit;

    n = philo->data->philo_num;
    if (n == 1)
        return philo->data->start_time;

    id = philo->id;
    k = n / 2;
    unit = philo->data->eat_time / k;

    if (unit == 0)
        unit = 1;

    printf("philo_num:%i id: %i wait_time: %i   check_k: %i  check_unit:%i \n",n,id,unit*((id*k)%n),k,unit);
    return ( unit * ((id * k)%n));
}

void	*philo_ploblem(void *some_philo)
{
	t_philo	*philo;
	int wait_time;

	philo = (t_philo *)some_philo;
	
	wait_time=calc_meal_time(philo);
	printf("id: %i  wait_time: %i\n",philo->id,wait_time);
	ft_strict_usleep(calc_meal_time(philo));
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
