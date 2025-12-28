/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processus_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 14:49:51 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/28 15:02:13 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	kill_processus(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (data->philo[i].pid > 0)
			kill(data->philo[i].pid, SIGKILL);
		i++;
	}
}

int	create_processus(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == -1)
			return (0);
		if (data->philo[i].pid == 0)
		{
			philo_routine(&data->philo[i]);
			exit(0);
		}
		i++;
	}
	return (1);
}

void	wait_processus(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->n_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_processus((data));
			break ;
		}
		i++;
	}
}
