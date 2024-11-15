/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:25:35 by marco             #+#    #+#             */
/*   Updated: 2024/11/15 15:17:56 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->lock_end);
	pthread_mutex_lock(&philo->lock_2);
	if (data->end == 1 || philo->state == 1)
	{
		pthread_mutex_unlock(&philo->lock_2);
		pthread_mutex_unlock(&data->lock_end);
		return ;
	}
	pthread_mutex_unlock(&philo->lock_2);
	pthread_mutex_unlock(&data->lock_end);
	if (check_state(data, philo))
		return ;
	print_state(SLEEPING, philo, data);
	ft_usleep(data->sleep_time);
	if (check_end(data, philo))
		return ;
	print_state(THINKING, philo, data);
}
