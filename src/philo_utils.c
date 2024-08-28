/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:37:07 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/27 13:10:19 by dhosokaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	protected_output(char *str, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->write));
	if (dead_check(philo->data) != 1)
		printf("%lu %i %s", get_time() - (philo->data->start_time), philo->id,
			str);
	pthread_mutex_unlock(&(philo->data->write));
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static long long	digits_process(const char *str, int sign, long long res)
{
	while (ft_isdigit(*str))
	{
		if (res > ((LONG_MAX - (*str - '0')) / 10))
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return ((int)digits_process(str, sign, res) * sign);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (i < n)
	{
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
		if (c1 == '\0' && c2 == '\0')
			return (0);
		if ((c1 == '\0' || c2 == '\0') || c1 != c2)
		{
			return (c1 - c2);
		}
		s1++;
		s2++;
		i++;
	}
	return (0);
}
