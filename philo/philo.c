/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:24:50 by mohaben-          #+#    #+#             */
/*   Updated: 2025/04/30 16:00:36 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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
	
	destroy_data_mutexs(&data);
	free(philos);
	return (0);
}
