/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 21:47:44 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/30 16:31:15 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	check_dead(t_philo *philo)
{
	long long	time;
	long long	last_eat;

	sem_wait(philo->data->eat_sem);
	last_eat = philo->last_eat;
	sem_post(philo->data->eat_sem);
	time = getting_time();
	if (time - last_eat > philo->data->die_time)
		return (1);
	return (0);
}

int	check_eat(t_philo *philo)
{
	int	n_eat;

	if (philo->data->n_time_eat_philo == -1)
		return (0);
	sem_wait(philo->data->eat_sem);
	n_eat = philo->n_eat;
	sem_post(philo->data->eat_sem);
	if (n_eat >= philo->data->n_time_eat_philo)
		return (1);
	return (0);
}

void	*check_philo_dead_eat(void *av)
{
	t_philo		*philo;
	long long	time_start;

	philo = (t_philo *)av;
	usleep(1000);
	while (1)
	{
		if (check_eat(philo))
			exit(0);
		if (check_dead(philo))
		{
			sem_wait(philo->data->print_sem);
			time_start = getting_time() - philo->data->time_start;
			printf("%lld %d died\n", time_start, philo->id);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}
