/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:59:48 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/22 18:45:21 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_alive(t_philosopher *philosopher)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	pthread_mutex_lock(philosopher->dtm);
	if (philosopher->constants->time_to_die < \
	(curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000) \
	- philosopher->death_timer && philosopher->death_timer != 0)
	{
		if (philosopher->dinner_times_needed != 0)
		{
			pthread_mutex_unlock(philosopher->dtm);
			pthread_mutex_lock(&philosopher->constants->print_mutex);
			printf("%ld %d is dead\n", timestamp(philosopher-> \
			constants->start_time), philosopher->id);
			return (0);
		}
	}
	pthread_mutex_unlock(philosopher->dtm);
	return (1);
}

void	*death_checker(t_data *data)
{
	int	i;

	while (1)
	{
		usleep(data->constants.time_to_die / 2);
		i = 0;
		pthread_mutex_lock(&data->constants.have_ate_num_mutex);
		if (data->constants.num_of_philo_have_ate \
		== data->constants.num_of_philos)
			break ;
		pthread_mutex_unlock(&data->constants.have_ate_num_mutex);
		while (i < data->constants.num_of_philos)
		{
			if (!is_alive(&data->philosophers[i]))
				return (NULL);
			i++;
		}
	}
	free_data(data);
	return (NULL);
}
