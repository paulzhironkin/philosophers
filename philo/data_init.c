/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:03:34 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/22 12:54:06 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_constants	const_init(int argc, char *argv[])
{
	t_constants		constants;
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	constants = (t_constants){
		.num_of_philos = get_int(argv[1]),
		.time_to_die = get_int(argv[2]),
		.time_to_eat = get_int(argv[3]),
		.time_to_sleep = get_int(argv[4]),
		.num_of_philo_must_eat = -1,
		.num_of_philo_have_ate = 0,
		.start_time = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000
	};
	if (constants.num_of_philos == 0)
		printf("Number of philosophers shoud be more than 0\n");
	if (argc == 6)
		constants.num_of_philo_must_eat = get_int(argv[5]);
	return (constants);
}

static int	mutexes_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->constants.num_of_philos)
	{
		if (pthread_mutex_init(&data->fork_mutexes[i], NULL) != 0)
		{
			while (i != 0)
				pthread_mutex_destroy(&data->fork_mutexes[--i]);
			return (error("Failed to initialze mutex."));
		}
		i++;
	}
	if (pthread_mutex_init(&data->constants.print_mutex, NULL) != 0)
		return (error("Failed to initialize print mutex."));
	if (pthread_mutex_init(&data->constants.have_ate_num_mutex, NULL) != 0)
		return (error("Failed to initialize have_ate_num_mutex."));
	return (0);
}

static int	dt_mutexes_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->constants.num_of_philos)
	{
		if (pthread_mutex_init(&data->dt_mutexes[i], NULL) != 0)
		{
			while (i != 0)
				pthread_mutex_destroy(&data->dt_mutexes[--i]);
			return (error("Failed to initialze mutex."));
		}
		i++;
	}
	return (0);
}

t_data	*data_init(int argc, char *argv[])
{
	t_data		*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->constants = const_init(argc, argv);
	data->philosophers = (t_philosopher *)malloc(sizeof(\
		t_philosopher) * data->constants.num_of_philos);
	data->threads = (pthread_t *)malloc(sizeof(\
		pthread_t) * data->constants.num_of_philos);
	data->fork_mutexes = (pthread_mutex_t *)malloc(sizeof(\
		pthread_mutex_t) * data->constants.num_of_philos);
	data->dt_mutexes = (pthread_mutex_t *)malloc(sizeof(\
		pthread_mutex_t) * data->constants.num_of_philos);
	if (!data || !data->philosophers || !data->threads \
		|| !data->fork_mutexes || mutexes_init(data) < 0 \
		|| data->constants.num_of_philos < 1 \
		|| data->constants.time_to_die < 0 \
		|| data->constants.time_to_eat < 0 \
		|| data->constants.time_to_sleep < 0 \
		|| (data->constants.num_of_philo_must_eat < 0 && argc == 6)
		|| dt_mutexes_init(data) < 0)
	{
		free_data(data);
		data = NULL;
	}
	return (data);
}
