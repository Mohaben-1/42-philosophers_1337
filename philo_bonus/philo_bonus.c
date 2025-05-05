/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:23:42 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/05 19:30:31 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_for_stop_and_kill(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->philos_nb)
	{
		kill(philos[i].philo_pid, SIGKILL);
		i++;
	}
}

void	stop_philos_death(t_philo *philos)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			wait_for_stop_and_kill(philos->data, philos);
	}
}

int	create_philos(t_philo *philos)
{
	pthread_t	meals_thread;
	int			i;

	i = 0;
	philos->data->start_time = get_current_time();
	while (i < philos->data->philos_nb)
	{
		philos[i].philo_pid = fork();
		if (philos[i].philo_pid == -1)
			return (print_error("Failed to create a proccess"));
		else if (philos[i].philo_pid == 0)
			routine(&philos[i]);
		i++;
	}
	if (philos->data->meals_required > 0)
	{
		if (pthread_create(&meals_thread, NULL, monitor_meals, philos->data))
			return (print_error("Failed to create monitor_meals thread"));
		pthread_detach(meals_thread);
	}
	stop_philos_death(philos);
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
