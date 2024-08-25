/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hosokawa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:06:09 by hosokawa          #+#    #+#             */
/*   Updated: 2024/08/10 12:02:29 by hosokawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_argument_number(char **argv)
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
			if (!isdigit(argv[i][j]))
				error_exit("error:need number value argument");
			j++;
		}
		i++;
	}
}

void	check_validation_arg(int argc, char **argv)
{
	if (argc > 6)
		error_exit("error:too many argument");
	if(argc<5)
		error_exit("error:too few argument");
	is_argument_number(argv);
}
