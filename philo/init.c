/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:46:30 by sryou             #+#    #+#             */
/*   Updated: 2022/11/07 14:18:58 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int	idx;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (data->fork == 0)
		return (1);
	idx = 0;
	while (idx < data->number_of_philosophers)
		pthread_mutex_init(&(data->fork[idx++]), NULL);
	pthread_mutex_init(&(data->print), NULL);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->check_number_of_times = 1;
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	}
	else
	{
		data->check_number_of_times = 0;
		data->number_of_times_each_philosopher_must_eat = 0;
	}
	data->isend = 0;
	if (init_mutex(data))
		return (1);
	if (is_wrong_argument(data))
		return (1);
	return (0);
}

void	init_philo(t_data *data, t_philo *philo, int idx)
{
	philo->id = idx;
	philo->count_eating = 0;
	philo->start_time = data->start_time;
	philo->eat_time = data->start_time;
	philo->data = data;
	philo->left_fork = idx;
	philo->right_fork = (idx + 1) % data->number_of_philosophers;
}
