/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjambo <jjambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:56:02 by jjambo            #+#    #+#             */
/*   Updated: 2025/10/15 14:35:41 by jjambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->rules->number_of_philosophers)
	{
		pthread_mutex_destroy(&philos->rules->mutex.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->rules->mutex.death_lock);
	pthread_mutex_destroy(&philos->rules->mutex.meal_lock);
	pthread_mutex_destroy(&philos->rules->mutex.time_to_died_mtx);
	pthread_mutex_destroy(&philos->rules->mutex.last_meal_time_lock);
	pthread_mutex_destroy(&philos->rules->mutex.write_lock);
	pthread_mutex_destroy(&philos->rules->mutex.finish);
	free(philos->rules->mutex.forks);
	free(philos);
}
