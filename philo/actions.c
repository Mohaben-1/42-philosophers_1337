/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:43:49 by mohaben-          #+#    #+#             */
/*   Updated: 2025/04/30 17:47:17 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo->data, philo->id, "has taken a fork");
}

void	eat(t_philo *philo)
{

}
void	release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_philo(t_philo *philo)
{

}

void	think(t_philo *philo)
{

}
