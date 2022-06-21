/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:07:58 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/21 12:49:17 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_constants {
	int			num_of_philos;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			num_of_philo_must_eat;
	long long	start_time;
}	t_constants;

typedef struct s_philosopher {
	t_constants	constants;
	int			id;
	int			dinner_times_needed;
	long long	death_timer;
	int			is_alive;
	sem_t		*forks;
	sem_t		*print_sem;
}	t_philosopher;

typedef struct s_data {
	t_constants		constants;
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*print_sem;
}	t_data;

t_data	*data_init(int argc, char *argv[]);
void	philo_take_forks(t_philosopher *philosopher);
void	philo_eat(t_philosopher *philosopher);
void	philo_sleep(t_philosopher *philosopher);
void	philo_think(t_philosopher *philosopher);
void	simulation(t_data *data, int i);
void	my_sleep(long long time);
void	*death_checker(t_data *data);
int		error(const char *line);
int		get_int(const char *str);
long	timestamp(long start_time);
void	my_sleep(long long time);
void	free_data(t_data *data);

#endif
