/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:45:30 by sryou             #+#    #+#             */
/*   Updated: 2022/11/07 15:08:06 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_philo_isalleat(t_data *data, t_philo *philosophers)
{
	int	idx;
	int	flag;

	if (data->check_number_of_times == 0)
		return (0);
	idx = 0;
	flag = 1;
	while (idx < data->number_of_philosophers)
	{
		if (philosophers[idx].count_eating < \
		data->number_of_times_each_philosopher_must_eat)
		{
			flag = 0;
			break ;
		}
		idx++;
	}
	return (flag);
}

void	ft_philo_isend(t_data *data, t_philo *philosophers)
{
	int	idx;

	while (1)
	{
		idx = 0;
		while ((idx < data->number_of_philosophers) && (!data->isend))
		{
			if ((ft_time() - philosophers[idx].eat_time) > data->time_to_die)
			{
				ft_printf(data, philosophers + idx, "died", 1);
				data->isend = 1;
			}
			idx++;
		}
		if (data->isend)
			break ;
		if (ft_philo_isalleat(data, philosophers))
			break ;
	}
}

void	ft_philo_finish(t_data *data, t_philo *philosophers)
{
	int	idx;

	idx = 0;
	while (idx < data->number_of_philosophers)
		pthread_detach(philosophers[idx++].pthread_id);
	idx = 0;
	while (idx < data->number_of_philosophers)
		pthread_mutex_destroy(&(data->fork[idx++]));
	pthread_mutex_destroy(&(data->print));
	free(data->fork);
	free(philosophers);
}

void	ft_philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->fork[philo->left_fork]));
	ft_printf(data, philo, "has taken a fork", 0);
	pthread_mutex_lock(&(data->fork[philo->right_fork]));
	ft_printf(data, philo, "has taken a fork", 0);
	ft_printf(data, philo, "is eating", 0);
	philo->eat_time = ft_time();
	ft_usleep(data, data->time_to_eat);
	philo->count_eating++;
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void	*ft_philo(void *argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = argv;
	data = philo->data;
	if (philo->id % 2 == 1)
		ft_usleep(data, data->time_to_eat);
	while (!data->isend)
	{
		ft_philo_eat(data, philo);
		if (data->isend)
			break ;
		ft_printf(data, philo, "is sleeping", 0);
		ft_usleep(data, data->time_to_sleep);
		if (data->isend)
			break ;
		ft_printf(data, philo, "is thinking", 0);
	}
	return (NULL);
}
