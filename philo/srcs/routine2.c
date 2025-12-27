/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 22:03:56 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/26 17:25:15 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_think(t_philo *philo)
{
	print_philo_action(philo, "is thinking");
}

void	single_philo(t_philo *philo)
{
	int	stop;

	print_philo_action(philo, "has taken a fork");
	while (1)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		stop = philo->data->stop;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (stop)
			return ;
		usleep(1000);
	}
}

void	init_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_eat = getting_time();
	pthread_mutex_unlock(&philo->data->eat_mutex);
	if (philo->id % 2 == 0)
		usleep(philo->data->eat_time * 500);
}

void	*philo_routine(void *av)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)av;
	init_philo_routine(philo);
	if (philo->data->n_philo == 1)
	{
		single_philo(philo);
		return (NULL);
	}
	stop = 0;
	while (!stop)
	{
		philo_think(philo);
		philo_take_fork(philo);
		philo_eat(philo);
		philo_put_fork(philo);
		philo_sleep(philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
		stop = philo->data->stop;
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	return (NULL);
}
