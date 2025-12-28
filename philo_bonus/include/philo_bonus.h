/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 23:05:24 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/28 14:57:31 by aghalmi          ###   ########.fr       */
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
	sem_t				*fork;
	sem_t				*print_sem;
	sem_t				*stop_sem;
	sem_t				*eat_sem;
}						t_data;

struct					s_philo
{
	int					id;
	long long			last_eat;
	int					n_eat;
	int					fork_left;
	int					fork_right;
	t_data				*data;
	pid_t				pid;
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
// init
int						init_semaphore(t_data *data);
int						init_philo(t_data *data);
int						init_data(t_data *data);
int						init(t_data *data);
// processus
void					kill_processus(t_data *data);
int						create_processus(t_data *data);
void					wait_processus(t_data *data);

#endif