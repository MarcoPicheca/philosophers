/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:01:41 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/05 12:08:06 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Serve per la stampa del tempo
unsigned	long	get_time(void)
{
	struct timeval	tv;
	unsigned long	res;

	res = 0;
	if (gettimeofday(&tv, NULL))
		return (printf("Error gettimeofday()\n"), 0);
	res = (tv.tv_sec * (unsigned long)1000) + (tv.tv_usec / 1000);
	return (res);
}

int	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return(0);
}
