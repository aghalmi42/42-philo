/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 20:10:08 by aghalmi           #+#    #+#             */
/*   Updated: 2025/12/25 21:54:22 by aghalmi          ###   ########.fr       */
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
	pthread_mutex_t		*fork;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_t			check_thread;
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

// Parsing
int						valid_num(char *str);
int						ft_atoi(char *str);
int						convert_and_check(char *str, int *dest);
int						parsing_and_save(int ac, char **av, t_data *data);
int						parsing_argument(int ac, char **av, t_data *data);
// initialisation
int						init_fork(t_data *data);
int						init_philo(t_data *data);
int						init_mutex(t_data *data);
int						init_data(t_data *data);
int						init(t_data *data);
// time
long long				getting_time(void);
void					init_time(t_data *data);
// routine
void					print_philo_action(t_philo *philo, char *action);
void					philo_take_fork(t_philo *philo);
void					philo_eat(t_philo *philo);
void					philo_put_fork(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					philo_think(t_philo *philo);
void					*philo_routine(void *av);
// thread
int						create_thread(t_data *data);
int						join_thread(t_data *data);
// check
int						philo_dead(t_data *data, int i);
int						check_eat_all(t_data *data);
int						check_condition(t_data *data);
void					*check_dead(void *av);
// free
void					destroy_mutex(t_data *data);
void					free_data(t_data *data);
void					free_all(t_data *data);
#endif