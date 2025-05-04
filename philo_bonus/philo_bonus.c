/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:23:42 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/04 16:50:19 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	sem_t	*sem;

	sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	if (sem == SEM_FAILED)
	{
		perror("sem_open failed");
		exit(EXIT_FAILURE);
	}
	sem_close(sem);
	sem_unlink(SEM_NAME);
	return (0);
}
