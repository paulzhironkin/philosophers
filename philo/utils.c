/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:23:46 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/19 16:14:10 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(const char *line)
{
	printf("Error: %s\n", line);
	return (-1);
}

int	get_int(const char *str)
{
	int	num;
	int	i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (error("Argument is not a natural number"));
		num = (str[i] - '0') + num * 10;
		i++;
	}
	return (num);
}

long	timestamp(long start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec \
		/ 1000) - start_time);
}

void	my_sleep(long long time)
{
	struct timeval	curr_time;
	long long		start_time;

	gettimeofday(&curr_time, NULL);
	start_time = curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	while (time > (curr_time.tv_sec \
	* 1000 + curr_time.tv_usec / 1000) - start_time)
	{
		gettimeofday(&curr_time, NULL);
		usleep(10);
	}
}
