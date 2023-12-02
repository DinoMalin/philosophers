/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:13:16 by jcario            #+#    #+#             */
/*   Updated: 2023/12/02 13:32:38 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	philo_new(t_env *env)
{
	t_philo			result;

	result.is_thinking = TRUE;
	result.is_eating = FALSE;
	result.is_sleeping = FALSE;
	result.alive = TRUE;
	result.last_sleep = 0;
	result.left_fork = FALSE;
	result.right_fork = FALSE;
	result.last_eat = get_time();
	result.nb_meals = 0;
	result.env = env;
	return (result);
}

int	check_av(int ac, char **av, t_env *env)
{
	int				i;
	int				j;

	if (ac > 6 || ac < 5)
		return (0);
	if (ac == 6)
	{
		env->nb_eat_defined = 1;
		env->nb_times_eat = ft_atoi(av[5]);
	}
	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j])
			if (!ft_isdigit(av[i][j++]))
				return (0);
	}
	env->nb_philos = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	env->start_time = get_time();
	pthread_mutex_init(&env->print, NULL);
	return (1);
}

void	init_philos(t_env *env)
{
	int		i;

	i = 0;
	env->philos = malloc(env->nb_philos * sizeof(t_philo));
	while (i < env->nb_philos)
	{
		env->philos[i] = philo_new(env);
		pthread_mutex_init(&env->philos[i].dead, NULL);
		pthread_mutex_init(&env->philos[i].meals, NULL);
		pthread_mutex_init(&env->philos[i].check_fork, NULL);
		env->philos[i].index = i + 1;
		i++;
	}
}

void	create_and_join_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_philos)
	{
		pthread_create(&env->philos[i].thread, NULL, thread, &env->philos[i]);
		usleep(1000);
		i++;
	}
	i = 0;
	while (i < env->nb_philos)
	{
		pthread_join(env->philos[i].thread, NULL);
		i++;
	}
}
