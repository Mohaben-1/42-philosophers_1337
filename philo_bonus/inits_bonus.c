/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:33:51 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 18:31:57 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sems_init(t_data *data)
{
	t_sems	*sems;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	sems = malloc(sizeof(t_sems));
	if (!sems)
		return (print_error("malloc failed for sems"));
	sems->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, data->philos_nb);
	sems->meal_sem = sem_open(SEM_MEAL, O_CREAT | O_EXCL, 0644, 0);
	sems->print_sem = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0644, 1);
	sems->stop_sem = sem_open(SEM_STOP, O_CREAT | O_EXCL, 0644, 1);
	if (sems->forks == SEM_FAILED || sems->meal_sem == SEM_FAILED
		|| sems->print_sem == SEM_FAILED || sems->stop_sem == SEM_FAILED)
	{
		free(sems);
		return (print_error("Failed to open semaphores!"));
	}
	data->sems = sems;
	return (1);
}

void	cleanup_sems(t_data *data)
{
	if (!data->sems)
		return ;
	sem_close(data->sems->forks);
	sem_close(data->sems->meal_sem);
	sem_close(data->sems->print_sem);
	sem_close(data->sems->stop_sem);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	free(data->sems);
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
	data->start_time = 0;
	data->sems = NULL;
	data->philos = NULL;
	if (!sems_init(data))
		return (0);
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
		(*philos)[i].data = data;
		i++;
	}
	return (1);
}
