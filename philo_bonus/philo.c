/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:35:47 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/21 16:07:28 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	termination(t_data *data)
{
	pid_t	killed_proc;
	int		i;

	i = 0;
	while (i != data->constants.num_of_philos)
	{
		waitpid(-1, &killed_proc, 0);
		if (killed_proc)
		{
			i = 0;
			while (i < data->constants.num_of_philos)
			{
				if (data->pids[i] != killed_proc)
					kill(data->pids[i], 9);
				i++;
			}
			break ;
		}
		else
			i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	if (argc != 5 && argc != 6)
		return (error("Invalid number of arguments"));
	data = data_init(argc, argv);
	i = -1;
	while (++i < data->constants.num_of_philos)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			error("Fork error!");
		if (data->pids[i] == 0)
		{
			simulation(data, i);
		}
	}
	termination(data);
	free_data(data);
	return (0);
}
