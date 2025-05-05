/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:28:07 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/05 19:30:45 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*death_monitoring(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->sems->stop_sem);
		if (get_current_time() - philo->last_meal_time >= philo->data->die_time)
		{
			print_state(philo->data, philo->id, "died");
			sem_post(philo->data->sems->stop_sem);
			i = 0;
			while (i < philo->data->philos_nb)
			{
				sem_post(philo->data->sems->required_sem);
				i++;
			}
			exit(1);
		}
		sem_post(philo->data->sems->stop_sem);
		usleep(500);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	i = 0;
	while (i < data->philos_nb)
	{
		sem_wait(data->sems->required_sem);
		i++;
	}
	sem_wait(data->sems->stop_sem);
	wait_for_stop_and_kill(data, data->philos);
	cleanup_sems(data);
	exit(0);
}

void	routine(t_philo *philo)
{
	pthread_t	monitor_thread;

	philo->last_meal_time = get_current_time();
	if (pthread_create(&monitor_thread, NULL, death_monitoring, philo))
		return ;
	pthread_detach(monitor_thread);
	while (1)
	{
		think(philo);
		pick_fork(philo);
		eat(philo);
		release_fork(philo);
		sleep_philo(philo);
		if (philo->data->meals_required > 0
			&& philo->meals_eaten == philo->data->meals_required)
			sem_post(philo->data->sems->required_sem);
	}
	exit(0);
}
