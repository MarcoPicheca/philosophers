/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:16:18 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/12 17:11:48 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL))
			return (printf("Problems mutex init_fork\n"));
		data->forks[i].id = i;
	}
	i = -1;
	return (0);
}

static	int	init_num(t_data *data, int i)
{
	data->philos[i].eat_time = data->eat_time; 
	data->philos[i].sleep_time = data->sleep_time;
	data->philos[i].meals_num = data->meals_num;
	if (pthread_mutex_init(&data->philos[i].lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->philos[i].lock_2, NULL))
		return (1);
	if (pthread_mutex_init(&data->philos[i].check_lock, NULL))
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;
	int	num;

	i = -1;
	num = 1;
	while (++i < data->philo_num)	
	{
		if (init_num(data, i))
			return (1);
		data->philos[i].th_id = num++;
		if (i != data->philo_num - 1)
		{
			data->philos[i].r_fork = &data->forks[i];
			data->philos[i].l_fork = &data->forks[i + 1];
		}
		if (i == data->philo_num - 1)
		{
			data->philos[i].r_fork = &data->forks[data->philo_num - 1];
			data->philos[i].l_fork = &data->forks[0];
		}
		data->philos[i].data = data;
	}
	return (0);
}

static	void	*one_philo(void *dt)
{
	t_data	*data;

	data = (t_data *)dt;
	data->sim_start = get_time();
	pthread_mutex_lock(&data->philos[0].r_fork->fork);
	print_state(TAKE_FORKS, &data->philos[0], data);
	ft_usleep(data->death_time);
	print_state(DIED, &data->philos[0], data);
	data->end = 1;
	pthread_mutex_unlock(&data->philos[0].r_fork->fork);
	pthread_mutex_destroy(&data->philos[0].r_fork->fork);
	return (NULL);
}

int	init_ph_fk(t_data *data)
{
	if (pthread_mutex_init(&data->lock_print, NULL))
		return (printf("Problems mutex init lock sv\n"));
	if (pthread_mutex_init(&data->lock_check, NULL))
		return (printf("Problems mutex init lock sv\n"));
	if (pthread_mutex_init(&data->lock_end, NULL))
		return (printf("Problems mutex init lock end\n"));
	if (init_forks(data))
		return (1);
	if (init_philos(data))
		return (1);
	if (data->philo_num == 1)
	{
		pthread_create(&data->philos[0].th_philo, NULL, one_philo, data);
		pthread_join(data->philos[0].th_philo, NULL);
		return(0);
	}
	data->supervisor[0].data = data;
	return (0);
}
