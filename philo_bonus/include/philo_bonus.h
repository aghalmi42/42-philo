/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 23:05:24 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/27 23:17:26 by aghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int					n_philo;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					n_time_eat_philo;
	int					stop;
	long long			time_start;
	t_philo				*philo;
}						t_data;

struct					s_philo
{
	int					id;
	long long			last_eat;
	int					n_eat;
	int					fork_left;
	int					fork_right;
	t_data				*data;
	pthread_t			thread;
};

// parsing
int						valid_num(char *str);
int						ft_atoi(char *str);
int						convert_and_check(char *str, int *dest);
int						parsing_and_save(int ac, char **av, t_data *data);
int						parsing_argument(int ac, char **av, t_data *data);
// time
void					init_time(t_data *data);
long long				getting_time(void);

#endif