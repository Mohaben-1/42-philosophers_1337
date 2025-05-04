/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:34:56 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 20:45:45 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(char *err)
{
	printf("%s\n", err);
	return (0);
}

unsigned long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(unsigned long duration)
{
	unsigned long	start;

	start = get_current_time();
	while (get_current_time() - start < duration)
		usleep(100);
}

void	print_state(t_data *data, int philo_id, char *state)
{
	unsigned long	timestamp;

	sem_wait(data->sems->print_sem);
	timestamp = get_current_time() - data->start_time;
	printf("%-4lu %-3d %s\n", timestamp, philo_id, state);
	sem_post(data->sems->print_sem);
}

void	wait_for_stop_and_kill(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	sem_wait(data->sems->stop_sem);
	while (i < data->philos_nb)
	{
		kill(philos[i].philo_pid, SIGKILL);
		i++;
	}
}
