/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:57:48 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/21 16:22:58 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philosopher	philo_init(t_data *data, int i)
{
	t_philosopher	philosopher;
	struct timeval	curr_time;

	philosopher.constants = data->constants;
	philosopher.dinner_times_needed = data->constants.num_of_philo_must_eat;
	philosopher.id = i + 1;
	philosopher.is_alive = 1;
	gettimeofday(&curr_time, NULL);
	philosopher.death_timer = \
	curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000;
	philosopher.forks = data->forks;
	philosopher.print_sem = data->print_sem;
	return (philosopher);
}

static void	*check_alive(void *data)
{
	t_philosopher	*philosopher;
	struct timeval	curr_time;

	philosopher = (t_philosopher *)data;
	gettimeofday(&curr_time, NULL);
	while (philosopher->is_alive)
	{
		if (((curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000) - \
			philosopher->death_timer) > philosopher->constants.time_to_die \
			&& philosopher->death_timer != 0)
		{
			philosopher->is_alive = 0;
			sem_wait(philosopher->print_sem);
			printf("%zd %d is dead\n", timestamp(philosopher-> \
			constants.start_time), philosopher->id);
			exit(1);
		}
		else
			gettimeofday(&curr_time, NULL);
	}
	return (NULL);
}

void	simulation(t_data *data, int i)
{
	t_philosopher	philosopher;
	pthread_t		death_thread;

	philosopher = philo_init(data, i);
	pthread_create(&death_thread, NULL, check_alive, (void *)&philosopher);
	pthread_detach(death_thread);
	while (philosopher.is_alive)
	{
		philo_take_forks(&philosopher);
		philo_eat(&philosopher);
		sem_post(data->forks);
		sem_post(data->forks);
		if (philosopher.dinner_times_needed != -1)
		{
			philosopher.dinner_times_needed--;
			if (!philosopher.dinner_times_needed)
			{
				exit(0);
			}
		}
		philo_sleep(&philosopher);
		philo_think(&philosopher);
	}
	exit(1);
}
