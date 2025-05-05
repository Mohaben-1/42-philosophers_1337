/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:34:56 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/05 15:07:04 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	print_error(char *err)
{
	printf("%s\n", err);
	return (0);
}

unsigned long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(unsigned long duration)
{
	unsigned long	start;

	start = get_current_time();
	while (get_current_time() - start < duration)
		usleep(100);
}

void	print_state(t_data *data, int philo_id, char *state)
{
	unsigned long	timestamp;

	sem_wait(data->sems->print_sem);
	timestamp = get_current_time() - data->start_time;
	printf("%-4lu %-3d %s\n", timestamp, philo_id, state);
	if (ft_strcmp(state, "died"))
		sem_post(data->sems->print_sem);
}
