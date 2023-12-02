/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcario <jcario@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:49:44 by jcario            #+#    #+#             */
/*   Updated: 2023/12/02 03:59:27 by jcario           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *msg, t_philo *philo)
{
	long long	time;

	time = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->print);
	printf("[%lld] %d %s\n", time, philo->index, msg);
	pthread_mutex_unlock(&philo->env->print);
}

int	check_meals(t_env *env)
{
	int	i;

	i = 0;
	if (!env->nb_eat_defined)
		return (FALSE);
	while (i < env->nb_philos)
	{
		if (get_meals(&env->philos[i]) < env->nb_times_eat)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	everyone_is_alive(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_philos)
	{
		if (!is_alive(&env->philos[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_philo	*get_next_philo(t_philo *philo, t_env *env, int pos)
{
	if (philo->index == 1 && pos == -1)
		return (&env->philos[env->nb_philos - 1]);
	else if (philo->index == env->nb_philos && pos == 1)
		return (&env->philos[0]);
	return (&env->philos[(philo->index - 1) + pos]);
}
