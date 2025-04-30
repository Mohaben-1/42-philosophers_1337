/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:24:50 by mohaben-          #+#    #+#             */
/*   Updated: 2025/04/30 17:47:29 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philo->data->stop_mutex));
		if (philo->data->stop_simulation)
		{
			pthread_mutex_unlock(&(philo->data->stop_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philo->data->stop_mutex));
		pick_fork(philo);
		eat(philo);
		release_fork(philo);
		sleep_philo(philo);
		think(philo);
	}
	return (NULL);
}

int	create_philos_thread(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_current_time();
	while (i < data->philos_nb)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, routine, &philo[i]))
			return (print_error("Failed to create thread"));
		i++;
	}
	i = 0;
	while (i < data->philos_nb)
	{
		if (pthread_join(philo[i].thread_id, NULL))
			return (print_error("Failed to join thread"));
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (!data_init(ac, av, &data))
		return (1);
	if (!philos_init(&philos, &data))
	{
		destroy_data_mutexs(&data);
		return (1);
	}
	if (!create_philos_thread(philos, &data))
	{
		destroy_data_mutexs(&data);
		free(philos);
		return (1);
	}
	destroy_data_mutexs(&data);
	free(philos);
	return (0);
}
