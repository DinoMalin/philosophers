/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 01:40:10 by jcario            #+#    #+#             */
/*   Updated: 2023/12/02 03:58:40 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_left_fork(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->check_fork);
	result = philo->left_fork;
	pthread_mutex_unlock(&philo->check_fork);
	return (result);
}

int	get_right_fork(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->check_fork);
	result = philo->right_fork;
	pthread_mutex_unlock(&philo->check_fork);
	return (result);
}

void	free_all(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_philos)
	{
		pthread_mutex_destroy(&env->philos[i].dead);
		pthread_mutex_destroy(&env->philos[i].meals);
		pthread_mutex_destroy(&env->philos[i].check_fork);
		i++;
	}
	pthread_mutex_destroy(&env->print);
	free(env->philos);
}

void	set_left_fork(t_philo *philo, int set)
{
	pthread_mutex_lock(&philo->check_fork);
	philo->left_fork = set;
	pthread_mutex_unlock(&philo->check_fork);
}

void	set_right_fork(t_philo *philo, int set)
{
	pthread_mutex_lock(&philo->check_fork);
	philo->right_fork = set;
	pthread_mutex_unlock(&philo->check_fork);
}
