/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjambo <jjambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:49:16 by jjambo            #+#    #+#             */
/*   Updated: 2025/10/20 09:51:55 by jjambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_vars_main	var;

	var.i = 0;
	if (!check_int_limits(ac, av))
		return (exit_with_error("Error: integer value out of range\n"), 1);
	if (!init_rules(&var.rules, ac, av))
		return (1);
	if (!check_arguments(&var.rules))
		return (1);
	var.philo = malloc(sizeof(t_philo) * var.rules.number_of_philosophers);
	while (var.i < var.rules.number_of_philosophers)
	{
		var.philo[var.i].rules = &var.rules;
		var.i++;
	}
	var.i = -1;
	if (!init_mutex(var.philo))
		return (1);
	init_philos(var.philo);
	pthread_create(&var.monitor_p, NULL, monitor, var.philo);
	while (++var.i < var.rules.number_of_philosophers)
		pthread_join(var.philo[var.i].thread, NULL);
	pthread_join(var.monitor_p, NULL);
	destroy_all(var.philo);
	return (0);
}
