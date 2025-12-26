/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 20:01:29 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/26 15:14:27 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_thread(t_data *data)
{
	int	i;

	i = 0;
	pthread_create(&data->check_thread, NULL, check_dead, data);
	while (i < data->n_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, philo_routine,
			&data->philo[i]);
		i++;
	}
	return (1);
}

int	join_thread(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->check_thread, NULL);
	while (i < data->n_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing_argument(ac, av, &data))
		return (1);
	if (!init(&data))
	{
		printf("ERROR\nFail init");
		return (1);
	}
	if (!create_thread(&data))
	{
		printf("ERROR\nFail create thread\n");
		return (1);
	}
	if (!join_thread(&data))
	{
		printf("ERROR\nFail join thread\n");
		return (1);
	}
	free_all(&data);
	return (0);
}
