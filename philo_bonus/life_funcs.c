/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:45:28 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/21 14:03:34 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philosopher *philosopher)
{
	sem_wait(philosopher->forks);
	sem_wait(philosopher->print_sem);
	printf("%ld %d has taken the fork\n", \
	timestamp(philosopher->constants.start_time), philosopher->id);
	sem_post(philosopher->print_sem);
	sem_wait(philosopher->forks);
	sem_wait(philosopher->print_sem);
	printf("%ld %d has taken the fork\n", \
	timestamp(philosopher->constants.start_time), philosopher->id);
	sem_post(philosopher->print_sem);
}

void	philo_eat(t_philosopher *philosopher)
{
	struct timeval	current_time;

	sem_wait(philosopher->print_sem);
	printf("%ld %d is eating\n", \
	timestamp(philosopher->constants.start_time), philosopher->id);
	sem_post(philosopher->print_sem);
	my_sleep(philosopher->constants.time_to_eat);
	gettimeofday(&current_time, NULL);
	philosopher->death_timer = \
	current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
}

void	philo_sleep(t_philosopher *philosopher)
{
	sem_wait(philosopher->print_sem);
	printf("%ld %d is sleeping\n", \
	timestamp(philosopher->constants.start_time), philosopher->id);
	sem_post(philosopher->print_sem);
	my_sleep(philosopher->constants.time_to_sleep);
}

void	philo_think(t_philosopher *philosopher)
{
	sem_wait(philosopher->print_sem);
	printf("%ld %d is thinking\n", \
	timestamp(philosopher->constants.start_time), philosopher->id);
	sem_post(philosopher->print_sem);
}
