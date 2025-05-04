/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:00:37 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 20:06:21 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
#include <signal.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>

# define SEM_FORKS "/sem_forks"
# define SEM_STOP "/sem_stop"
# define SEM_PRINT "/sem_print"
# define SEM_MEAL "/sem_meal"

typedef	struct	s_sems
{
	sem_t			*forks;
	sem_t			*stop_sem;
	sem_t			*print_sem;
	sem_t			*meal_sem;
}	t_sems;

typedef struct s_data
{
	int				philos_nb;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	unsigned long	start_time;
	int				meals_required;
	struct s_philo	*philos;
	t_sems			*sems;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal_time;
	pid_t			philo_pid;
	t_data			*data;
}	t_philo;

//Utils
int				print_error(char *err);
unsigned long	ft_atoi(const char *str);
void			ft_usleep(unsigned long duration);
unsigned long	get_current_time(void);
void			print_state(t_data *data, int philo_id, char *state);


void			wait_for_stop_and_kill(t_data *data, t_philo *philos);

//Init structs
int				data_init(int ac, char **av, t_data *data);
int				philos_init(t_philo **philos, t_data *data);

void			cleanup_sems(t_data *data);



//Actions
void			pick_fork(t_philo *philo);
void			eat(t_philo *philo);
void			release_fork(t_philo *philo);
void			sleep_philo(t_philo *philo);
void			think(t_philo *philo);

#endif