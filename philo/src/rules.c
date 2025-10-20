/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjambo <jjambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:17:59 by jjambo            #+#    #+#             */
/*   Updated: 2025/10/20 09:56:02 by jjambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isalnum(char c)
{
	return ((c >= '0' && c <= '9'));
}

static int	valid_input(int argc, char **argv)
{
	int	i;
	int	y;
	int	z;

	i = 1;
	y = 0;
	while (i < argc)
	{
		if (argv[i][y] == '+' || argv[i][y] == '-')
			y++;
		i++;
	}
	i = 1;
	while (i < argc)
	{
		z = y;
		while (argv[i][z])
			if (!ft_isalnum(argv[i][z++]))
				return (exit_with_error(
						"Error: arguments must be numeric\n"), 0);
		i++;
	}
	return (1);
}

int	init_rules(t_rules *rules, int ac, char **av)
{
	int	i;

	i = 0;
	if (!rules)
		return (0);
	if (!valid_input(ac, av))
		return (0);
	if (ac == 5 || ac == 6)
	{
		rules->time_to_die = ft_atoi(av[2]);
		rules->number_of_philosophers = ft_atoi(av[1]);
		rules->time_to_eat = ft_atoi(av[3]);
		rules->time_to_sleep = ft_atoi(av[4]);
		rules->control.someone_died = 0;
		if (ac == 6)
			rules->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		else
			rules->number_of_times_each_philosopher_must_eat = -1;
	}
	else
		return (
			exit_with_error(
				"Format: ./philo n t_die t_eat t_sleep [t_must_eat]"), 0);
	return (1);
}

int	check_int_limits(int ac, char **av)
{
	int		i;
	long	number;

	i = 1;
	while (i < ac)
	{
		number = ft_atoi(av[i]);
		if (number > INT_MAX)
			return (0);
		else if (number < INT_MIN)
			return (0);
		i++;
	}
	return (1);
}

int	check_arguments(t_rules *rules)
{
	if (rules->number_of_philosophers <= 0)
		return (exit_with_error("Error: invalid number of philosophers\n"), 0);
	else if (rules->number_of_philosophers > 200)
		return (exit_with_error("Error: too many philosophers\n"), 0);
	else if (rules->time_to_die <= 0)
		return (exit_with_error("Error: invalid time_to_die\n"), 0);
	else if (rules->time_to_eat <= 0)
		return (exit_with_error("Error: invalid time_to_eat\n"), 0);
	else if (rules->time_to_sleep <= 0)
		return (exit_with_error("Error: invalid time_to_sleep\n"), 0);
	else if (rules->time_to_eat <= 60 || rules->time_to_sleep <= 60)
		return (exit_with_error("Error: time too short (<60ms)\n"), 0);
	else if (rules->number_of_times_each_philosopher_must_eat != -1
		&& rules->number_of_times_each_philosopher_must_eat <= 0)
		return (exit_with_error("Error: invalid eat count\n"), 0);
	return (1);
}
