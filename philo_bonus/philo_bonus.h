/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:00:37 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 16:58:11 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>

# define SEM_NAME "/philo_sem"

typedef struct s_data
{
	int				philos_nb;
	unsigned long	die_time;
	unsigned long	eat_time;
	unsigned long	sleep_time;
	unsigned long	start_time;
	int				meals_required;
	sem_t			*forks;
	sem_t			*stop_sem;
	sem_t			*print_sem;
	sem_t			*meal_sem;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	unsigned long	last_meal_time;
	pid_t			philo_pid;
	t_data			*data;
}	t_philo;

#endif