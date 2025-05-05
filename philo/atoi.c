/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohaben- <mohaben-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 11:36:12 by mohaben-          #+#    #+#             */
/*   Updated: 2025/05/05 19:50:12 by mohaben-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_atoi(const char *str)
{
	unsigned long	res;

	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (0);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (res > (ULONG_MAX - (*str - '0')) / 10)
			return (0);
		res = res * 10 + (*str++ - '0');
	}
	return (res);
}
