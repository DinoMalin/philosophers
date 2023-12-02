/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_any.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 02:44:44 by jcario            #+#    #+#             */
/*   Updated: 2023/12/02 03:45:19 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->dead);
	result = philo->alive;
	pthread_mutex_unlock(&philo->dead);
	return (result);
}

void	kill_philo(t_philo *philo)
{
	if (!everyone_is_alive(philo->env))
		return ;
	pthread_mutex_lock(&philo->dead);
	philo->alive = FALSE;
	pthread_mutex_unlock(&philo->dead);
}

int	get_meals(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->meals);
	result = philo->nb_meals;
	pthread_mutex_unlock(&philo->meals);
	return (result);
}

void	increment_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->meals);
	philo->nb_meals += philo->env->nb_eat_defined;
	pthread_mutex_unlock(&philo->meals);
}
