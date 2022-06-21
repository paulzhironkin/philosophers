/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 16:31:24 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/21 15:26:05 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = data->constants.num_of_philos - 1;
	while (i > 0)
	{
		pthread_mutex_destroy(&data->fork_mutexes[i]);
		pthread_mutex_destroy(&data->dt_mutexes[i]);
		i--;
	}
	if (data->fork_mutexes)
		free(data->fork_mutexes);
	pthread_mutex_destroy(&data->constants.have_ate_num_mutex);
	pthread_mutex_destroy(&data->constants.print_mutex);
	if (data->constants.num_of_philos > 0)
	{
		pthread_mutex_destroy(data->fork_mutexes);
		pthread_mutex_destroy(data->dt_mutexes);
	}
	if (data->threads)
		free(data->threads);
	if (data->philosophers)
		free(data->philosophers);
	free(data);
	data = NULL;
}
