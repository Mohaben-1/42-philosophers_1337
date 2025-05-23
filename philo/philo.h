/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:23:30 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/05 19:50:30 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_data
{
	int				philos_nb;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	int				meals_required;
	int				stop_simulation;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

//Init structs
int				data_init(int ac, char **av, t_data *data);
int				philos_init(t_philo **philos, t_data *data);
void			destroy_data_mutexs(t_data *data);

//Utils
unsigned long	ft_atoi(const char *str);
int				print_error(char *err);
unsigned long	get_current_time(void);
void			print_state(t_data *data, int id, char *state);
void			ft_usleep(unsigned long duration, t_data *data);
int				check_stop(t_philo *philo);

//Actions
void			pick_fork(t_philo *philo);
void			eat(t_philo *philo);
void			release_fork(t_philo *philo);
void			sleep_philo(t_philo *philo);
void			think(t_philo *philo);

//Routine
void			*routine(void *arg);
int				check_meals_complete(t_data *data);
void			*single_routine(void *arg);

//Monitoring
void			*monitor_death(void *arg);

#endif
