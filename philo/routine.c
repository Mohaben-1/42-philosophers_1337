/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:30 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/01 20:14:22 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals_complete(t_data *data)
{
	int	completed_meals;
	int	i;

	completed_meals = 1;
	if (data->meals_required <= 0)
		return (0);
	pthread_mutex_lock(&data->meal_mutex);
	i = 0;
	while (i++ < data->philos_nb)
	{
		if (data->philos->meals_eaten < data->meals_required)
		{
			completed_meals = 0;
			break ;
		}
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (completed_meals)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	return (0);
}
