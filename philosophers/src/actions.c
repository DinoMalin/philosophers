/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 03:47:41 by jcario            #+#    #+#             */
/*   Updated: 2023/12/02 03:51:41 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	philo->is_eating = TRUE;
	philo->last_eat = get_time();
	if (everyone_is_alive(philo->env))
		print_msg("is eating", philo);
	increment_meals(philo);
	while (get_time() <= philo->last_eat + philo->env->time_to_eat
		&& is_alive(philo))
		if (get_time() >= philo->last_eat + philo->env->time_to_die)
			kill_philo(philo);
	set_left_fork(philo, FALSE);
	set_right_fork(philo, FALSE);
}

void	philo_think(t_philo *philo)
{
	philo->is_sleeping = FALSE;
	philo->is_thinking = TRUE;
	if (everyone_is_alive(philo->env) && !check_meals(philo->env))
		print_msg("is thinking", philo);
}

void	philo_sleep(t_philo *philo)
{
	philo->is_eating = FALSE;
	philo->is_sleeping = TRUE;
	philo->last_sleep = get_time();
	if (everyone_is_alive(philo->env) && !check_meals(philo->env))
		print_msg("is sleeping", philo);
	while (get_time() <= philo->last_sleep + philo->env->time_to_sleep
		&& is_alive(philo))
	{
		if (get_time() >= philo->last_eat + philo->env->time_to_die)
			kill_philo(philo);
	}
	philo_think(philo);
}
