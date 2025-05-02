/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:24:50 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/02 20:22:28 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_death(void *arg)
{
	t_data			*data;
	unsigned long	time_since_last_meal;
	int				i;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop_simulation)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		if (check_meals_complete(data))
			break ;
		i = 0;
		while (i < data->philos_nb)
		{
			pthread_mutex_lock(&data->meal_mutex);
			time_since_last_meal = get_current_time() - data->philos[i].last_meal_time;
			pthread_mutex_unlock(&data->meal_mutex);
			if (time_since_last_meal >= data->die_time)
			{
				pthread_mutex_lock(&data->stop_mutex);
				if (!data->stop_simulation)
				{
					print_state(data, data->philos[i].id, "died");
					data->stop_simulation = 1;
					pthread_mutex_unlock(&data->stop_mutex);
					return (NULL);
				}
				pthread_mutex_unlock(&data->stop_mutex);
				return (NULL);
			}
			i++;
			usleep(100);
		}
	}
	return (NULL);
}



void	*single_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_state(philo->data, philo->id, "has taken a fork");
	ft_usleep(philo->data->die_time, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->data->stop_mutex);
	philo->data->stop_simulation = 1;
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (philo->id % 2 == 0)
		usleep((philo->data->eat_time / 2) * 1000);
	while (1)
	{
		think(philo);
		pick_fork(philo);
		eat(philo);
		release_fork(philo);
		sleep_philo(philo);
		if (check_stop(philo))
			return (NULL);
	}
	return (NULL);
}

int	create_philos_thread(t_philo *philo, t_data *data)
{
	pthread_t	monitor_thread;
	int	i;

	i = 0;
	data->start_time = get_current_time();
	if (data->philos_nb == 1)
		pthread_create(&philo[0].thread_id, NULL, single_philo_routine, &philo[0]);
	else
	{
		while (i < data->philos_nb)
		{
			if (pthread_create(&(philo[i].thread_id), NULL, routine, &philo[i]))
				return (print_error("Failed to create thread"));
			i++;
		}	
	}
	if (pthread_create(&monitor_thread, NULL, monitor_death, data))
		return (print_error("Failed to create monitor thread"));
	i = 0;
	while (i < data->philos_nb)
	{
		if (pthread_join(philo[i].thread_id, NULL))
			return (print_error("Failed to join thread"));
		i++;
	}
	pthread_join(monitor_thread, NULL);
	return (1);
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
