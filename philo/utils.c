/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:39:09 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/01 18:46:22 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	print_state(t_data *data, int philo_id, char *state)
{
	unsigned long	timestamp;

	pthread_mutex_lock(&data->print_mutex);
	timestamp = get_current_time() - data->start_time;
	if (ft_strcmp(state, "died") == 0)
		printf("%lu %d %s\n", timestamp, philo_id, state);
	else
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (!data->stop_simulation)
			printf("%lu %d %s\n", timestamp, philo_id, state);
		pthread_mutex_unlock(&data->stop_mutex);
	}
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
			break;
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
