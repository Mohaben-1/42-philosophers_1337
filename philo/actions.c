/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:43:49 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/01 16:14:56 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo->data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo->data, philo->id, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex); 
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex); 
	print_state(philo->data, philo->id, "is eating");
	ft_usleep(philo->data->eat_time, philo->data);
}

void	release_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	sleep_philo(t_philo *philo)
{
	print_state(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->data->sleep_time, philo->data);
}

void	think(t_philo *philo)
{
	print_state(philo->data, philo->id, "is thinking");
}
