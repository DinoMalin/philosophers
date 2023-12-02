/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:03:04 by jcario            #+#    #+#             */
/*   Updated: 2023/12/02 03:51:59 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	take_forks(t_philo *philo)
{
	if (!get_right_fork(get_next_philo(philo, philo->env, 1))
		&& !get_left_fork(philo))
	{
		if (everyone_is_alive(philo->env) && !check_meals(philo->env))
			print_msg("has taken a fork LEFT", philo);
		set_left_fork(philo, TRUE);
	}
	if (!get_left_fork(get_next_philo(philo, philo->env, 1))
		&& !get_right_fork(philo))
	{
		if (everyone_is_alive(philo->env) && !check_meals(philo->env))
			print_msg("has taken a fork RIGHT", philo);
		set_right_fork(philo, TRUE);
	}
}

void	*thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (is_alive(philo) && everyone_is_alive(philo->env)
		&& !check_meals(philo->env))
	{
		if (philo->is_thinking && (!get_left_fork(philo)
				|| !get_right_fork(philo)))
			take_forks(philo);
		if (get_left_fork(philo) && get_right_fork(philo))
			philo_eat(philo);
		if (philo->is_eating)
			philo_sleep(philo);
		if (get_time() >= philo->last_eat + philo->env->time_to_die)
			kill_philo(philo);
	}
	if (!is_alive(philo) && !check_meals(philo->env))
		print_msg("died", philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	static t_env	env = {};

	if (!check_av(ac, av, &env))
		return (1);
	init_philos(&env);
	create_and_join_threads(&env);
	free_all(&env);
}
