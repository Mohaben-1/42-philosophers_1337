/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:30 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 13:19:15 by mohaben-         ###   ########.fr       */
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
		if (data->philos[i].meals_eaten < data->meals_required)
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

void	*single_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_state(philo->data, philo->id, "is thinking");
	print_state(philo->data, philo->id, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
	ft_usleep(philo->data->die_time, philo->data);
	print_state(philo->data, philo->id, "died");
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	think(philo);
	if (philo->id % 2 == 1)
		usleep((philo->data->eat_time / 2) * 1000);
	while (1)
	{
		pick_fork(philo);
		eat(philo);
		release_fork(philo);
		sleep_philo(philo);
		think(philo);
		if (check_stop(philo))
			return (NULL);
	}
	return (NULL);
}
