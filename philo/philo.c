/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:45:30 by sryou             #+#    #+#             */
/*   Updated: 2022/11/12 16:49:23 by sryou            ###   ########.fr       */
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
		pthread_mutex_lock(&(data->mutex_count_eating));
		if (philosophers[idx].count_eating < \
		data->number_of_times_each_philosopher_must_eat)
			flag = 0;
		pthread_mutex_unlock(&(data->mutex_count_eating));
		if (flag == 0)
			break ;
		idx++;
	}
	if (flag)
	{
		pthread_mutex_lock(&(data->mutex_isend));
		data->isend = 1;
		pthread_mutex_unlock(&(data->mutex_isend));
	}
	return (flag);
}

void	ft_philo_isend(t_data *data, t_philo *philosophers)
{
	int	idx;
	int	isbreak;

	isbreak = 0;
	while (1)
	{
		idx = 0;
		while ((idx < data->number_of_philosophers) && !isbreak)
		{
			pthread_mutex_lock(&(data->mutex_eat_time));
			if ((ft_time() - philosophers[idx].eat_time) > data->time_to_die)
			{
				ft_printf(data, philosophers + idx, "died");
				pthread_mutex_lock(&(data->mutex_isend));
				data->isend = 1;
				isbreak = 1;
				pthread_mutex_unlock(&(data->mutex_isend));
			}
			pthread_mutex_unlock(&(data->mutex_eat_time));
			idx++;
		}
		if (isbreak || ft_philo_isalleat(data, philosophers))
			break ;
		ft_usleep(1);
	}
}

void	ft_philo_finish(t_data *data, t_philo *philosophers)
{
	int	idx;

	idx = 0;
	if (data->number_of_philosophers == 1)
		pthread_detach(philosophers[0].pthread_id);
	else
		while (idx < data->number_of_philosophers)
			pthread_join(philosophers[idx++].pthread_id, NULL);
	idx = 0;
	while (idx < data->number_of_philosophers)
		pthread_mutex_destroy(&(data->fork[idx++]));
	pthread_mutex_destroy(&(data->mutex_isend));
	pthread_mutex_destroy(&(data->mutex_eat_time));
	pthread_mutex_destroy(&(data->mutex_count_eating));
	free(data->fork);
	free(philosophers);
}

int	ft_philo_eat(t_data *data, t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&(data->fork[philo->left_fork]));
	ret = ft_printf(data, philo, "has taken a fork");
	pthread_mutex_lock(&(data->fork[philo->right_fork]));
	ret = ft_printf(data, philo, "has taken a fork");
	ret = ft_printf(data, philo, "is eating");
	pthread_mutex_lock(&(data->mutex_eat_time));
	philo->eat_time = ft_time();
	pthread_mutex_unlock(&(data->mutex_eat_time));
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&(data->mutex_count_eating));
	philo->count_eating++;
	pthread_mutex_unlock(&(data->mutex_count_eating));
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
	return (ret);
}

void	*ft_philo(void *argv)
{
	t_philo	*philo;
	t_data	*data;

	philo = argv;
	data = philo->data;
	if (philo->id % 2 == 1)
		ft_usleep(data->time_to_eat);
	while (1)
	{
		if (ft_philo_eat(data, philo))
			break ;
		if (ft_printf(data, philo, "is sleeping"))
			break ;
		ft_usleep(data->time_to_sleep);
		if (ft_printf(data, philo, "is thinking"))
			break ;
	}
	return (NULL);
}
