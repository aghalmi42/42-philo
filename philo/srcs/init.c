/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:25:55 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/25 21:59:05 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->fork)
		return (0);
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return (1);
}

int	init_philo(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (0);
	return (1);
}

int	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].fork_left = i;
		data->philo[i].fork_right = (i + data->n_philo - 1) % data->n_philo;
		data->philo[i].last_eat = data->time_start;
		data->philo[i].n_eat = 0;
		data->philo[i].data = data;
		i++;
	}
	return (1);
}

int	init(t_data *data)
{
	if (!init_fork(data))
		return (0);
	if (!init_philo(data))
		return (0);
	if (!init_mutex(data))
		return (0);
	init_time(data);
	if (!init_data(data))
		return (0);
	data->stop = 0;
	return (1);
}
