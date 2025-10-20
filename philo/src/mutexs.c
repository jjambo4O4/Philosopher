/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjambo <jjambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:03:55 by jjambo            #+#    #+#             */
/*   Updated: 2025/10/17 12:28:20 by jjambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo *philo)
{
	int	i;

	philo->rules->mutex.forks = malloc(sizeof(pthread_mutex_t)
			* philo->rules->number_of_philosophers);
	i = 0;
	if (!philo->rules->mutex.forks)
		return (exit_with_error("Ocorreu um erro ao alocar os forks !\n"), 0);
	while (i < philo->rules->number_of_philosophers)
	{
		pthread_mutex_init(&philo->rules->mutex.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&philo->rules->mutex.death_lock, NULL);
	pthread_mutex_init(&philo->rules->mutex.meal_lock, NULL);
	pthread_mutex_init(&philo->rules->mutex.time_to_died_mtx, NULL);
	pthread_mutex_init(&philo->rules->mutex.last_meal_time_lock, NULL);
	pthread_mutex_init(&philo->rules->mutex.write_lock, NULL);
	pthread_mutex_init(&philo->rules->mutex.finish, NULL);
	return (1);
}
