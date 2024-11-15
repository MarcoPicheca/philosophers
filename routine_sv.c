/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_sv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:31:30 by marco             #+#    #+#             */
/*   Updated: 2024/11/15 12:25:21 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	check_philo_sv(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].lock);
	pthread_mutex_lock(&data->lock_end);
	if (data->philos[i].meals_num != 0
		&& (get_time() - data->philos[i].last_meal) > data->death_time)
	{
		data->philos[i].state = 1;
		data->end = 1;
		pthread_mutex_unlock(&data->lock_end);
		print_state(DIED, &data->philos[i], data);
		pthread_mutex_unlock(&data->philos[i].lock);
		return (1);
	}
	pthread_mutex_unlock(&data->lock_end);
	pthread_mutex_unlock(&data->philos[i].lock);
	return (0);
}

void	*routine_sv(void *dt)
{
	t_data			*data;
	static int		i = 0;

	data = (t_data *)dt;
	while (++i)
	{
		usleep(1);
		if (data->philos[i].th_id == 0)
			i = 1;
		pthread_mutex_lock(&data->lock_end);
		if (data->end == 1)
			return (NULL);
		pthread_mutex_unlock(&data->lock_end);
		if (check_philo_sv(data, i))
			return (NULL);
		pthread_mutex_lock(&data->philos[i].lock);
		if (data->philos[i].meals_num == 0)
		{
			data->philos[i].state = 1;
			pthread_mutex_unlock(&data->philos[i].lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->philos[i].lock);
	}
	return (NULL);
}
