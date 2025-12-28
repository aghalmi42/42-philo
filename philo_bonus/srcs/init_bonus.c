/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:34:11 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/28 14:46:35 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	init_semaphore(t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/stop");
	sem_unlink("/eat");
	data->fork = sem_open("/fork", O_CREAT | O_EXCL, 0644, data->n_philo);
	if (data->fork == SEM_FAILED)
		return (0);
	data->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (0);
	data->stop_sem = sem_open("/stop", O_CREAT | O_EXCL, 0644, 1);
	if (data->stop_sem == SEM_FAILED)
		return (0);
	data->eat_sem = sem_open("/eat", O_CREAT | O_EXCL, 0644, 1);
	if (data->eat_sem == SEM_FAILED)
		return (0);
	return (1);
}

int	init_philo(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philo)
		return (0);
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = data->time_start;
		data->philo[i].n_eat = 0;
		data->philo[i].data = data;
		data->philo[i].pid = 0;
		i++;
	}
	return (1);
}

int	ini(t_data *data)
{
	if (!init_semaphore(data))
		return (0);
	if (!init_philo(data))
		return (0);
	init_time(data);
	if (!init_data(data))
		return (0);
	data->stop = 0;
	return (1);
}
