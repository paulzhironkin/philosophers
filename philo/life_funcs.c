/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:45:28 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/19 16:28:05 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(&philosopher->constants->print_mutex);
	printf("%ld %d has taken the left fork\n", \
	timestamp(philosopher->constants->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->constants->print_mutex);
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(&philosopher->constants->print_mutex);
	printf("%ld %d has taken the right fork\n", \
	timestamp(philosopher->constants->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->constants->print_mutex);
}

void	philo_eat(t_philosopher *philosopher)
{
	struct timeval	current_time;

	pthread_mutex_lock(&philosopher->constants->print_mutex);
	printf("%ld %d is eating\n", \
	timestamp(philosopher->constants->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->constants->print_mutex);
	my_sleep(philosopher->constants->time_to_eat);
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philosopher->dtm);
	philosopher->death_timer = \
	current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	pthread_mutex_unlock(philosopher->dtm);
}

void	philo_sleep(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->constants->print_mutex);
	printf("%ld %d is sleeping\n", \
	timestamp(philosopher->constants->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->constants->print_mutex);
	my_sleep(philosopher->constants->time_to_sleep);
}

void	philo_think(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->constants->print_mutex);
	printf("%ld %d is thinking\n", \
	timestamp(philosopher->constants->start_time), philosopher->id);
	pthread_mutex_unlock(&philosopher->constants->print_mutex);
}
