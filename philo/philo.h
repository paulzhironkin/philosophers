/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:07:58 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/22 12:57:58 by latahbah         ###   ########.fr       */
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

typedef struct s_constants {
	int				num_of_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				num_of_philo_must_eat;
	int				num_of_philo_have_ate;
	long long		start_time;
	pthread_mutex_t	have_ate_num_mutex;
	pthread_mutex_t	print_mutex;
}	t_constants;

typedef struct s_philosopher {
	t_constants		*constants;
	pthread_t		*thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*dtm;
	int				id;
	int				dinner_times_needed;
	long long		death_timer;
}	t_philosopher;

typedef struct s_data {
	t_constants		constants;
	t_philosopher	*philosophers;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	*dt_mutexes;
	pthread_t		*threads;
}	t_data;

int		error(const char *line);
int		get_int(const char *str);
void	free_data(t_data *data);
t_data	*data_init(int argc, char *argv[]);
long	timestamp(long start_time);
void	philo_take_forks(t_philosopher *philosopher);
void	philo_eat(t_philosopher *philosopher);
void	philo_sleep(t_philosopher *philosopher);
void	philo_think(t_philosopher *philosopher);
void	my_sleep(long long time);
void	*death_checker(t_data *data);
int		simulation(t_data *data);

#endif
