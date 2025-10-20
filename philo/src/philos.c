/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjambo <jjambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:03:40 by jjambo            #+#    #+#             */
/*   Updated: 2025/10/16 13:48:21 by jjambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philo)
{
	int	i;

	i = 0;
	philo->rules->control.start_time = time_current();
	while (i < (philo)->rules->number_of_philosophers)
	{
		philo[i].finished = 0;
		philo[i].id = i + 1;
		philo[i].fork_left = i;
		philo[i].fork_right = (i + 1) % philo->rules->number_of_philosophers;
		philo[i].last_meal_time = philo->rules->control.start_time;
		i++;
	}
	i = 0;
	while (i < philo->rules->number_of_philosophers)
	{
		pthread_create(&philo[i].thread, NULL, routines, &philo[i]);
		if (i % 2 == 0)
			usleep(1000);
		i++;
	}
}

void	print_status(t_philo *philo, char *msg)
{
	if (!check_death(philo->rules))
	{
		pthread_mutex_lock(&philo->rules->mutex.write_lock);
		printf("%ld %d %s\n", time_current() - philo->rules->control.start_time,
			philo->id, msg);
		pthread_mutex_unlock(&philo->rules->mutex.write_lock);
	}
}

void	get_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 && !check_death(philo->rules))
	{
		pthread_mutex_lock(&philo->rules->mutex.forks[philo->fork_right]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->rules->mutex.forks[philo->fork_left]);
		print_status(philo, "has taken a fork");
	}
	else if (philo->id % 2 != 0 && !check_death(philo->rules))
	{
		pthread_mutex_lock(&philo->rules->mutex.forks[philo->fork_left]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->rules->mutex.forks[philo->fork_right]);
		print_status(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->rules->mutex.forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->rules->mutex.forks[philo->fork_right]);
}

int	check_death(t_rules *rules)
{
	int		death;

	pthread_mutex_lock(&rules->mutex.death_lock);
	death = rules->control.someone_died;
	pthread_mutex_unlock(&rules->mutex.death_lock);
	return (death);
}
