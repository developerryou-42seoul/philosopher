/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sryou <sryou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 03:11:22 by sryou             #+#    #+#             */
/*   Updated: 2022/11/07 14:56:06 by sryou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				check_number_of_times;
	int				number_of_times_each_philosopher_must_eat;
	int				isend;
	long long		start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			count_eating;
	long long	eat_time;
	long long	start_time;
	int			left_fork;
	int			right_fork;
	t_data		*data;
	pthread_t	pthread_id;
}	t_philo;

int			init_data(t_data *data, int argc, char **argv);
void		init_philo(t_data *data, t_philo *philo, int idx);

int			is_wrong_argument(t_data *data);
int			ft_atoi(char *str);
void		ft_printf(t_data *data, t_philo *philo, char *str, int islock);
long long	ft_time(void);
void		ft_usleep(t_data *data, long long ms);

void		*ft_philo(void *argv);
void		ft_philo_isend(t_data *data, t_philo *philosophers);
void		ft_philo_finish(t_data *data, t_philo *philosophers);

#endif