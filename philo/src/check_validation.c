/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:06:09 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/26 15:06:09 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_sutable_argv(int argc)
{
	if (argc > 6)
	{
		printf("error:too many argument\n");
		return (1);
	}
	if (argc < 5)
	{
		printf("error:too few argument\n");
		return (1);
	}
	return (0);
}

int	is_argument_number(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("error:need number value argument\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	is_sutable_number(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 1)
		{
			printf("need more than number 0 \n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_validation_arg(int argc, char **argv)
{
	if (is_sutable_argv(argc) == 1)
		return (1);
	if (is_argument_number(argv) == 1)
		return (1);
	if (is_sutable_number(argv) == 1)
		return (1);
	return (0);
}
