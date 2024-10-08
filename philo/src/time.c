/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:11:17 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/31 12:16:32 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "gettimeofday() error\n", 22);
		return (0);
	}
	return ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000));
}

void	ft_strict_usleep(u_int64_t time)
{
	u_int64_t	start;
	u_int64_t	remain_time;

	start = get_time();
	while (get_time() - start < time)
	{
		remain_time = time - (get_time() - start);
		if (remain_time > time / 10)
			usleep(time / 10);
		else
			usleep(remain_time);
	}
}

int	calc_wait_time(t_philo *philo)
{
	int	n;
	int	id;
	int	k;
	int	unit;

	n = philo->data->philo_num;
	if (n == 1)
		return (0);
	id = philo->id;
	k = n / 2;
	unit = philo->data->eat_time / k;
	if (unit == 0)
		unit = 1;
	return (unit * ((id * k) % n));
}
