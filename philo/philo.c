/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:35:47 by latahbah          #+#    #+#             */
/*   Updated: 2022/06/21 15:15:26 by latahbah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data		*data;

	if (argc != 5 && argc != 6)
		return (error("Invalid number of arguments"));
	data = data_init(argc, argv);
	if (!data)
	{
		return (0);
	}
	else
	{
		simulation(data);
		free(data);
	}
	return (0);
}
