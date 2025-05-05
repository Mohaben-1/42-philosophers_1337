/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:43:49 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/05 19:27:14 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_fork(t_philo *philo)
{
	sem_wait(philo->data->sems->forks);
	print_state(philo->data, philo->id, "has taken a fork");
	sem_wait(philo->data->sems->forks);
	print_state(philo->data, philo->id, "has taken a fork");
}

void	eat(t_philo *philo)
{
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	print_state(philo->data, philo->id, "is eating");
	ft_usleep(philo->data->eat_time);
}

void	release_fork(t_philo *philo)
{
	sem_post(philo->data->sems->forks);
	sem_post(philo->data->sems->forks);
}

void	sleep_philo(t_philo *philo)
{
	print_state(philo->data, philo->id, "is sleeping");
	ft_usleep(philo->data->sleep_time);
}

void	think(t_philo *philo)
{
	print_state(philo->data, philo->id, "is thinking");
}
