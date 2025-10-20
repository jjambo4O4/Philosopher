/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjambo <jjambo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:54:53 by jjambo            #+#    #+#             */
/*   Updated: 2025/10/20 09:11:48 by jjambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;

typedef enum e_flags
{
	DIED,
	EATING,
	SLEEPING,
	THINKING
}						t_flags;

typedef struct s_control
{
	int					someone_died;
	int					must_eat_count;
	long				start_time;
}						t_control;

typedef struct s_mtx
{
	t_mtx				*forks;
	t_mtx				death_lock;
	t_mtx				meal_lock;
	t_mtx				time_to_died_mtx;
	t_mtx				last_meal_time_lock;
	t_mtx				write_lock;
	t_mtx				finish;
}						t_mtxs;

typedef struct s_rules
{
	int					number_of_philosophers;
	int					number_of_times_each_philosopher_must_eat;
	long				time_to_sleep;
	long				time_to_eat;
	long				time_to_die;
	t_mtxs				mutex;
	t_control			control;
}						t_rules;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					fork_left;
	int					fork_right;
	int					last_meal_time;
	int					meals_eaten;
	t_rules				*rules;
	t_flags				status;
	int					finished;

}						t_philo;

typedef struct s_vars_main
{
	t_rules				rules;
	t_philo				*philo;
	int					i;
	pthread_t			monitor_p;

}						t_vars_main;

long					time_current(void);
void					ft_sleep(long time, t_philo *philo);
void					eating(t_philo *philo);
void					exit_with_error(char *msg);
int						init_mutex(t_philo *philo);
int						init_rules(t_rules *rules, int ac, char **av);
long					ft_atoi(const char *str);
void					*monitor(void *data);
void					thinking(t_philo *philo);
void					sleeping(t_philo *philo);
void					*routines(void *data);
void					init_philos(t_philo *philo);
void					print_status(t_philo *philo, char *msg);
void					get_forks(t_philo *philo);
void					release_forks(t_philo *philo);
int						check_death(t_rules *rules);
void					destroy_all(t_philo *philos);
void					you_can_move_one(long time_to_died, t_philo *philo,
							int *count);
int						has_eaten_enough(t_philo *philo);
int						check_arguments(t_rules *rules);
int						check_int_limits(int ac, char **av);
#endif
