/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:03:14 by jcario            #+#    #+#             */
/*   Updated: 2023/12/02 03:57:57 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0

typedef struct s_philo
{
	int				alive;
	long			last_eat;
	long			last_sleep;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	int				nb_meals;
	int				left_fork;
	int				right_fork;
	int				index;
	pthread_t		thread;
	pthread_mutex_t	dead;
	pthread_mutex_t	meals;
	pthread_mutex_t	check_fork;
	struct s_env	*env;
}	t_philo;

typedef struct s_env
{
	int				nb_philos;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	int				nb_times_eat;
	int				nb_eat_defined;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	print;
}	t_env;

int		check_av(int ac, char **av, t_env *env);
void	init_philos(t_env *env);
void	create_and_join_threads(t_env *env);
t_philo	philo_new(t_env *env);

int		check_meals(t_env *env);
void	print_msg(char *msg, t_philo *philo);
int		everyone_is_alive(t_env *env);
t_philo	*get_next_philo(t_philo *philo, t_env *env, int pos);

void	*thread(void *arg);
long	get_time(void);

int		get_right_fork(t_philo *philo);
int		get_left_fork(t_philo *philo);
void	free_all(t_env *env);
void	set_left_fork(t_philo *philo, int set);
void	set_right_fork(t_philo *philo, int set);

int		is_alive(t_philo *philo);
void	kill_philo(t_philo *philo);
int		get_meals(t_philo *philo);
void	increment_meals(t_philo *philo);

void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);

#endif