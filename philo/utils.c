/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:39:09 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 13:18:38 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_state(t_data *data, int philo_id, char *state)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	timestamp = get_current_time() - data->start_time;
	if (!data->stop_simulation)
		printf("%-4lu %-3d %s\n", timestamp, philo_id, state);
	pthread_mutex_unlock(&data->print_mutex);
}

void	ft_usleep(unsigned long duration, t_data *data)
{
	unsigned long	start;

	start = get_current_time();
	while (get_current_time() - start < duration)
	{
		usleep(100);
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
	}
}

int	check_stop(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(&philo->data->stop_mutex);
	stop = philo->data->stop_simulation;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (stop);
}
