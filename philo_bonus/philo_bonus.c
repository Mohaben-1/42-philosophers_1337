/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:23:42 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/05 16:43:48 by mohaben-         ###   ########.fr       */
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

void	*death_monitoring(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->sems->stop_sem);
		if (get_current_time() - philo->last_meal_time >= philo->data->die_time)
		{
			print_state(philo->data, philo->id, "died");
			sem_post(philo->data->sems->stop_sem);
			exit(1);
		}
		sem_post(philo->data->sems->stop_sem);
		usleep(500);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_data *data;
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
	free(data->philos);
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

int	create_philos(t_philo *philos)
{
	int	i;
	int	status;
	pthread_t	meals_thread;

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
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
			wait_for_stop_and_kill(philos->data, philos);
	}
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
