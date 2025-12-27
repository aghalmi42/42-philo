/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:34:43 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/22 16:52:22 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	valid_num(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] == '+')
		i = 1;
	else
		i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (str[0] == '+')
		i = 1;
	while (str[i])
	{
		if (result > INT_MAX / 10)
			return (-1);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result);
}

int	convert_and_check(char *str, int *dest)
{
	int	result;

	if (!valid_num(str))
	{
		printf("ERROR\nNot valid num\n");
		return (0);
	}
	result = ft_atoi(str);
	if (result == -1)
	{
		printf("ERROR\nNum is so large\n");
		return (0);
	}
	*dest = result;
	return (1);
}

int	parsing_and_save(int ac, char **av, t_data *data)
{
	if (!convert_and_check(av[1], &data->n_philo))
		return (0);
	if (!convert_and_check(av[2], &data->die_time))
		return (0);
	if (!convert_and_check(av[3], &data->eat_time))
		return (0);
	if (!convert_and_check(av[4], &data->sleep_time))
		return (0);
	if (ac == 6)
	{
		if (!convert_and_check(av[5], &data->n_time_eat_philo))
			return (0);
	}
	else
		data->n_time_eat_philo = -1;
	return (1);
}

int	parsing_argument(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
	{
		printf("ERROR\nLess number of argument\n");
		return (1);
	}
	if (!parsing_and_save(ac, av, data))
		return (1);
	if (data->n_philo <= 0 || data->die_time <= 0 || data->eat_time <= 0
		|| data->sleep_time <= 0)
	{
		printf("ERROR\nValue is not positive\n");
		return (1);
	}
	if (ac == 6 && data->n_time_eat_philo <= 0)
	{
		printf("ERROR\nNumber of eat is not positive\n");
		return (1);
	}
	return (0);
}
