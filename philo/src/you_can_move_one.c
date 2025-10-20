/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   you_can_move_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjambo <jjambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:54:27 by jjambo            #+#    #+#             */
/*   Updated: 2025/10/16 11:58:56 by jjambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	has_eaten_enough(t_philo *philo)
{
	int	number_of_times;

	number_of_times = philo->rules->number_of_times_each_philosopher_must_eat;
	if (philo->rules->number_of_times_each_philosopher_must_eat > 0)
	{
		if (philo->meals_eaten == number_of_times)
			return (1);
	}
	return (0);
}

void	you_can_move_one(long time_to_died, t_philo *philo, int *count)
{
	long	now;

	now = time_current();
	if (time_to_died >= philo->rules->time_to_die)
	{
		if (!check_death(philo->rules))
		{
			pthread_mutex_lock(&philo->rules->mutex.death_lock);
			philo->rules->control.someone_died = 1;
			pthread_mutex_unlock(&philo->rules->mutex.death_lock);
			now = time_current();
			pthread_mutex_lock(&philo->rules->mutex.write_lock);
			printf("%ld %d died\n", now - philo->rules->control.start_time,
				philo->id);
			pthread_mutex_unlock(&philo->rules->mutex.write_lock);
		}
	}
	pthread_mutex_lock(&philo->rules->mutex.meal_lock);
	if (!philo->finished && has_eaten_enough(philo))
	{
		philo->finished = 1;
		(*count)++;
	}
	pthread_mutex_unlock(&philo->rules->mutex.meal_lock);
}
