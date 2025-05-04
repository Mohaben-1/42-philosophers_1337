/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:43:49 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 13:10:09 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->stop_mutex);
	print_state(philo->data, philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->data->stop_mutex);
	print_state(philo->data, philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex); 
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex); 
	pthread_mutex_lock(&philo->data->stop_mutex);
	print_state(philo->data, philo->id, "is eating");
	pthread_mutex_unlock(&philo->data->stop_mutex);
	ft_usleep(philo->data->eat_time, philo->data);
}

void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop_mutex);
	print_state(philo->data, philo->id, "is sleeping");
	pthread_mutex_unlock(&philo->data->stop_mutex);
	ft_usleep(philo->data->sleep_time, philo->data);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->stop_mutex);
	print_state(philo->data, philo->id, "is thinking");
	pthread_mutex_unlock(&philo->data->stop_mutex);
}
