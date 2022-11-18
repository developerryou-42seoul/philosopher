/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:41:12 by sryou             #+#    #+#             */
/*   Updated: 2022/11/12 16:48:11 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	runprocess(t_data *data)
{
	t_philo	*philosophers;
	int		idx;

	philosophers = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (philosophers == 0)
		return ;
	idx = 0;
	data->start_time = ft_time();
	while (idx < data->number_of_philosophers)
	{
		init_philo(data, philosophers + idx, idx);
		if (pthread_create(&(philosophers[idx].pthread_id), \
			NULL, ft_philo, philosophers + idx))
			return ;
		idx++;
	}
	ft_philo_isend(data, philosophers);
	ft_philo_finish(data, philosophers);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (init_data(&data, argc, argv))
			return (1);
		runprocess(&data);
	}
	return (0);
}
