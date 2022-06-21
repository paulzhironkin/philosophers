/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:03:34 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/21 16:11:16 by latahbah         ###   ########.fr       */
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
		.start_time = cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000
	};
	if (constants.num_of_philos == 0)
		error("Num of philos should be more than 0");
	if (argc == 6)
		constants.num_of_philo_must_eat = get_int(argv[5]);
	return (constants);
}

static void	semaphores_initialization(t_data *data)
{
	sem_unlink("sem.forks");
	sem_unlink("sem.print");
	sem_unlink("sem.have_ate");
	data->forks = sem_open("sem.forks", O_CREAT, 0644, \
	data->constants.num_of_philos);
	data->print_sem = sem_open("sem.print", O_CREAT, 0644, 1);
}

t_data	*data_init(int argc, char *argv[])
{
	t_data		*data;

	data = (t_data *)malloc(sizeof(t_data));
	data->constants = const_init(argc, argv);
	data->pids = (pid_t *)malloc(sizeof(pid_t) * data->constants.num_of_philos);
	semaphores_initialization(data);
	if (!data || !data->pids || data->forks == SEM_FAILED \
		|| data->print_sem == SEM_FAILED)
		error("Failed while initialization!");
	return (data);
}
