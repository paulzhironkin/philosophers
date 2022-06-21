/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:57:48 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/21 14:55:14 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_life(t_philosopher *philosopher)
{
	philo_take_forks(philosopher);
	philo_eat(philosopher);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
	if (philosopher->dinner_times_needed != -1)
	{
		philosopher->dinner_times_needed--;
		if (!philosopher->dinner_times_needed)
		{
			pthread_mutex_lock(&philosopher->constants->have_ate_num_mutex);
			philosopher->constants->num_of_philo_have_ate += 1;
			pthread_mutex_unlock(&philosopher->constants->have_ate_num_mutex);
			return (0);
		}
	}
	philo_sleep(philosopher);
	philo_think(philosopher);
	return (1);
}

static void	*philo_thread(void *data)
{
	t_philosopher	*philosopher;
	struct timeval	current_time;

	philosopher = (t_philosopher *)data;
	pthread_detach(*philosopher->thread_id);
	gettimeofday(&current_time, NULL);
	if (philosopher->id % 2 == 0)
		usleep(200);
	pthread_mutex_lock(philosopher->dtm);
	philosopher->death_timer = \
	current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	pthread_mutex_unlock(philosopher->dtm);
	while (1)
	{
		if (!philo_life(philosopher))
			break ;
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->constants.num_of_philos)
	{
		data->philosophers[i] = (t_philosopher){
			.constants = &data->constants,
			.id = i + 1,
			.dinner_times_needed = data->constants.num_of_philo_must_eat,
			.thread_id = &data->threads[i],
			.left_fork = &data->fork_mutexes[i],
			.right_fork = \
			&data->fork_mutexes[(i + 1) % data->constants.num_of_philos],
			.dtm = &data->dt_mutexes[i]
		};
		pthread_create(&data->threads[i], NULL, \
			philo_thread, (void *)&data->philosophers[i]);
		i++;
	}
	death_checker(data);
}
