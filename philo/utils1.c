/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:04:19 by sryou             #+#    #+#             */
/*   Updated: 2022/11/18 16:19:57 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;

	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	res = 0;
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

int	is_wrong_argument(t_data *data)
{
	if (data->number_of_philosophers <= 0 || \
		data->time_to_eat <= 0 || \
		data->time_to_sleep <= 0 || \
		data->time_to_die <= 0 || \
		data->number_of_times_each_philosopher_must_eat < 0)
		return (1);
	if (data->check_number_of_times && \
		data->number_of_times_each_philosopher_must_eat == 0)
		return (1);
	return (0);
}
