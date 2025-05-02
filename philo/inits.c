/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:50:59 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/02 20:30:55 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *err)
{
	printf("%s\n", err);
	return (0);
}

int	create_data_mutexs(t_data *data)
{
	int	i;

	data->forks = malloc(data->philos_nb * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	i = -1;
	while (++i < data->philos_nb)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(data->forks[i]));
			free(data->forks);
			return (0);
		}
	}
	if (pthread_mutex_init(&(data->stop_mutex), NULL)
		|| pthread_mutex_init(&(data->print_mutex), NULL) || pthread_mutex_init(&(data->meal_mutex), NULL))
	{
		while (--i >= 0)
			pthread_mutex_destroy(&(data->forks[i]));
		free(data->forks);
		return (0);
	}
	return (1);
}

void	destroy_data_mutexs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->stop_mutex));
	pthread_mutex_destroy(&(data->print_mutex));
	pthread_mutex_destroy(&(data->meal_mutex));
	free(data->forks);
}

int	data_init(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (print_error("Invalid number of arguments!"));
	data->philos_nb = ft_atoi(av[1]);
	if (data->philos_nb <= 0 || data->philos_nb > 200)
		return (print_error("Invalid number of philosophers!"));
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (data->die_time < 60 || data->eat_time < 60 || data->sleep_time < 60)
		return (print_error("Invalid time!"));
	if (ac == 6)
	{
		data->meals_required = ft_atoi(av[5]);
		if (data->meals_required < 0)
			return (print_error("Invalid number of required meals!"));
	}
	else
		data->meals_required = -1;
	data->stop_simulation = 0;
	data->start_time = 0;
	if (!create_data_mutexs(data))
		return (print_error("Failed to create Mutex!"));
	return (1);
}

int	philos_init(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(data->philos_nb * sizeof(t_philo));
	if (!*philos)
		return (0);
	i = 0;
	while (i < data->philos_nb)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].last_meal_time = 0;
		(*philos)[i].left_fork = &data->forks[i];
		(*philos)[i].right_fork = &data->forks[(i + 1) % data->philos_nb];
		(*philos)[i].data = data;
		i++;
	}
	return (1);
}
