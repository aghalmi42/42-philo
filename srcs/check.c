/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 19:17:21 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/25 22:10:51 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_dead(t_data *data, int i)
{
	long long	time;
	long long	last_eat;

	pthread_mutex_lock(&data->eat_mutex);
	last_eat = data->philo[i].last_eat;
	pthread_mutex_unlock(&data->eat_mutex);
	time = getting_time();
	if (time - last_eat > data->die_time)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n", time - data->time_start, data->philo[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	return (0);
}

int	check_eat_all(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (data->n_time_eat_philo == -1)
		return (0);
	while (i < data->n_philo)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->philo[i].n_eat >= data->n_time_eat_philo)
			count++;
		pthread_mutex_unlock(&data->eat_mutex);
		i++;
	}
	if (count == data->n_philo)
		return (1);
	return (0);
}

int	check_condition(t_data *data)
{
	int	i;

	i = 0;
	if (check_eat_all(data))
		return (1);
	while (i < data->n_philo)
	{
		if (philo_dead(data, i))
			return (1);
		i++;
	}
	return (0);
}

void	*check_dead(void *av)
{
	t_data	*data;

	data = (t_data *)av;
	usleep(1000);
	while (1)
	{
		if (check_condition(data))
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		usleep(5000);
	}
	return (NULL);
}
