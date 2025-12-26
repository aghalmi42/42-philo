/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:41:11 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/26 15:14:44 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_philo_action(t_philo *philo, char *action)
{
	long long	time_start;
	int			stop;

	pthread_mutex_lock(&philo->data->stop_mutex);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	if (stop)
		return ;
	time_start = getting_time() - philo->data->time_start;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", time_start, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	philo_take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->fork[philo->fork_left]);
		print_philo_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
		print_philo_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->fork_right]);
		print_philo_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->fork[philo->fork_left]);
		print_philo_action(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	int	stop;

	print_philo_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_eat = getting_time();
	pthread_mutex_unlock(&philo->data->eat_mutex);
	usleep(philo->data->eat_time * 1000);
	pthread_mutex_lock(&philo->data->stop_mutex);
	stop = philo->data->stop;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	if (!stop)
	{
		pthread_mutex_lock(&philo->data->eat_mutex);
		philo->n_eat++;
		pthread_mutex_unlock(&philo->data->eat_mutex);
	}
}

void	philo_put_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->fork[philo->fork_right]);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_action(philo, "is sleeping");
	usleep(philo->data->sleep_time * 1000);
}
