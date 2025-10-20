/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjambo <jjambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:02:58 by jjambo            #+#    #+#             */
/*   Updated: 2025/10/17 11:46:00 by jjambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	if (philo->rules->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->rules->mutex.forks[philo->fork_left]);
		print_status(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->rules->mutex.forks[philo->fork_left]);
		while (!philo->rules->control.someone_died)
			usleep(1000);
	}
	else
	{
		get_forks(philo);
		pthread_mutex_lock(&philo->rules->mutex.last_meal_time_lock);
		philo->last_meal_time = time_current();
		pthread_mutex_unlock(&philo->rules->mutex.last_meal_time_lock);
		print_status(philo, "is eating");
		pthread_mutex_lock(&philo->rules->mutex.meal_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->rules->mutex.meal_lock);
		ft_sleep(philo->rules->time_to_eat, philo);
		release_forks(philo);
	}
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_sleep(philo->rules->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	long	time_thinking;

	print_status(philo, "is thinking");
	time_thinking = philo->rules->time_to_die - philo->rules->time_to_eat
		- philo->rules->time_to_sleep;
	if (time_thinking > 0)
		ft_sleep(time_thinking / 2, philo);
	else
		usleep(1000);
}

void	*routines(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!check_death(philo->rules))
	{
		eating(philo);
		if (has_eaten_enough(philo))
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*monitor(void *data)
{
	t_philo	*philo;
	int		i;
	int		count_;
	int		time_to_died;

	count_ = 0;
	philo = (t_philo *)data;
	while (!check_death(philo->rules))
	{
		i = 0;
		while (i < philo->rules->number_of_philosophers)
		{
			pthread_mutex_lock(&philo->rules->mutex.last_meal_time_lock);
			time_to_died = time_current() - philo[i].last_meal_time;
			pthread_mutex_unlock(&philo->rules->mutex.last_meal_time_lock);
			you_can_move_one(time_to_died, &philo[i], &count_);
			if (check_death(philo->rules))
				return (NULL);
			i++;
		}
		if (count_ == philo->rules->number_of_philosophers)
			break ;
		usleep(1000);
	}
	return (NULL);
}
