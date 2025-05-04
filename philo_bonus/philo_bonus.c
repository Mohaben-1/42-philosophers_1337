/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:23:42 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 20:46:30 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo)
{
	sem_wait(philo->data->sems->meal_sem);
	philo->last_meal_time = get_current_time();
	sem_post(philo->data->sems->meal_sem);
	while (1)
	{
		think(philo);
		pick_fork(philo);
		eat(philo);
		release_fork(philo);
		sleep_philo(philo);
	}
}

int	create_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->philos_nb)
	{
		philos[i].philo_pid = fork();
		if (philos[i].philo_pid == -1)
			return (print_error("Failed to create a proccess"));
		else if (philos[i].philo_pid == 0)
		{
			routine(&philos[i]);
			exit(0);
		}
		i++;
	}
	wait_for_stop_and_kill(philos->data, philos);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (!data_init(ac, av, &data))
		return (1);
	if (data.meals_required == 0)
	{
		cleanup_sems(&data);
		return (0);
	}
	if (!philos_init(&philos, &data))
	{
		cleanup_sems(&data);
		return (1);
	}
	data.philos = philos;
	if (!create_philos(philos))
	{
		cleanup_sems(&data);
		free(philos);
		return (1);
	}
	free(philos);
	cleanup_sems(&data);
	return (0);
}
