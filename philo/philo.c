/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:24:50 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 12:22:46 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosopher_threads(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_current_time();
	if (data->philos_nb == 1)
	{
		if (pthread_create(&philo[0].thread, NULL, single_routine, &philo[0]))
			return (print_error("Failed to create thread"));
		return (1);
	}
	while (++i < data->philos_nb)
	{
		if (pthread_create(&(philo[i].thread), NULL, routine, &philo[i]))
			return (print_error("Failed to create thread"));
	}
	return (1);
}

int	wait_for_threads(t_philo *philo, t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	if (data->philos_nb > 1)
	{
		if (pthread_create(&monitor_thread, NULL, monitor_death, data))
			return (print_error("Failed to create monitor thread"));
	}
	i = -1;
	while (++i < data->philos_nb)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (print_error("Failed to join thread"));
	}
	if (data->philos_nb > 1)
		pthread_join(monitor_thread, NULL);
	return (1);
}

int	create_philos_thread(t_philo *philo, t_data *data)
{
	if (!create_philosopher_threads(philo, data))
		return (0);
	return (wait_for_threads(philo, data));
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;

	if (!data_init(ac, av, &data))
		return (1);
	if (data.meals_required == 0)
	{
		destroy_data_mutexs(&data);
		return (0);
	}
	if (!philos_init(&philos, &data))
	{
		destroy_data_mutexs(&data);
		return (1);
	}
	data.philos = philos;
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
