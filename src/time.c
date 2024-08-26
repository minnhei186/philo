/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:11:17 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/26 14:48:59 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
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
