/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:39:09 by mohaben-          #+#    #+#             */
/*   Updated: 2025/04/30 17:41:08 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_current_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_state(t_data *data, int id, char *print)
{
	unsigned long	timestamp;

	timestamp = get_current_time() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	printf("%lu %d %s\n", timestamp, id, print);
	pthread_mutex_unlock(&data->print_mutex);
}
