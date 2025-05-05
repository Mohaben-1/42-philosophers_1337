/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 11:45:27 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/05 16:00:26 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop_simulation(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

int	check_philosopher_death(t_philo *philo, t_data *data)
{
	unsigned long	time_since_last_meal;

	pthread_mutex_lock(&data->meal_mutex);
	time_since_last_meal = get_current_time() - philo->last_meal_time;
	pthread_mutex_unlock(&data->meal_mutex);
	if (time_since_last_meal >= data->die_time)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (!data->stop_simulation)
		{
			print_state(data, philo->id, "died");
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!should_stop_simulation(data))
	{
		if (check_meals_complete(data))
			return (NULL);
		i = 0;
		while (i < data->philos_nb)
		{
			if (check_philosopher_death(&data->philos[i], data))
				return (NULL);
			i++;
			usleep(100);
		}
	}
	return (NULL);
}
