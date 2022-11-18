/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:04:19 by sryou             #+#    #+#             */
/*   Updated: 2022/11/12 16:27:58 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(long long ms)
{
	long long	current_time;

	current_time = ft_time();
	while (ft_time() - current_time < ms)
		usleep(10);
}

long long	ft_time(void)
{
	struct timeval	time;
	long long		ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

int	ft_printf(t_data *data, t_philo *philo, char *str)
{
	int	ret;

	ret = 1;
	pthread_mutex_lock(&(data->mutex_isend));
	if (!data->isend)
	{
		printf("%lld %d %s\n", \
			ft_time() - philo->start_time, philo->id + 1, str);
		ret = 0;
	}
	pthread_mutex_unlock(&(data->mutex_isend));
	return (ret);
}
