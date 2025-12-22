/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:10:08 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/22 16:54:16 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int	n_philo;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	n_time_eat_philo;
}		t_data;

// Parsing
int		valid_num(char *str);
int		ft_atoi(char *str);
int		convert_and_check(char *str, int *dest);
int		parsing_and_save(int ac, char **av, t_data *data);
int		parsing_argument(int ac, char **av, t_data *data);
#endif