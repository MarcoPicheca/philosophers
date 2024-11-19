/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:56:18 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/19 14:47:20 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_state(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->lock_check);
	if ((get_time() - philo->last_meal) > data->death_time)
	{
		pthread_mutex_lock(&data->lock_end);
		data->end = 1;
		pthread_mutex_unlock(&data->lock_end);
		print_state(DIED, philo, data);
		pthread_mutex_unlock(&data->lock_check);
		return (1);
	}
	pthread_mutex_unlock(&data->lock_check);
	return (0);
}

int	check_end(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->lock_end);
	if (data->end == 1 || philo->state == 1)
	{
		pthread_mutex_unlock(&data->lock_end);
		return (1);
	}
	pthread_mutex_unlock(&data->lock_end);
	return (0);
}

void	*routine(void *dt)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)dt;
	if (philo->th_id % 2 != 0)
		ft_usleep(10);
	data = philo->data;
	while (!check_end(data, philo))
	{
		eating(philo, data);
		sleeping(philo, data);
		if (check_end(data, philo))
			return (NULL);
	}
	return (NULL);
}

static	int	start_routine2(t_data *data, int i)
{
	data->philos[i].last_meal = data->sim_start;
	if (i == data->philo_num)
	{
		if (pthread_create(&data->supervisor[0].sv, NULL, routine_sv, data))
			return (1);
	}
	else if (i < data->philo_num
		&& pthread_create(&data->philos[i].th_philo
			, NULL, routine, &data->philos[i]))
		return (1);
	return (0);
}

int	start_routine(t_data *data)
{
	int	i;

	i = -1;
	data->sim_start = get_time();
	while (++i <= data->philo_num)
	{
		if (start_routine2(data, i))
			return (ft_putstr_len("Problems in creating a thread\n"));
	}
	i = -1;
	if (pthread_join(data->supervisor[0].sv, NULL))
		return (ft_putstr_len("Problems in joining a thread\n"));
	while (++i < data->philo_num)
	{
		if (pthread_join(data->philos[i].th_philo, NULL))
			return (ft_putstr_len("Problems in joining a thread\n"));
	}
	return (0);
}
