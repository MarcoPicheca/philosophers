/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:56:18 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/12 18:15:28 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_data *data, t_philo *philo)
{
	ft_usleep(1);
	pthread_mutex_lock(&data->lock_check);
	if ((get_time() - philo->last_meal) > data->death_time)
	{
		// pthread_mutex_lock(&data->lock_end);
		ft_putstr_len("porco dio per 3 ");
		ft_putchar_len('\n');
		data->end = 1;
		philo->state = 1;
		// pthread_mutex_unlock(&data->lock_end);
		print_state(DIED, philo, data);
		pthread_mutex_unlock(&data->lock_check);
		return (1);
	}
	// ft_putnbr_len(philo->th_id);
	pthread_mutex_unlock(&data->lock_check);
	return (0);
}

void	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->lock_2);
	if (data->end == 1 || philo->state == 1)
	{
		pthread_mutex_unlock(&philo->lock_2);
		return ;
	}
	pthread_mutex_unlock(&philo->lock_2);
	if (check_state(data, philo))
		return ;
	///////////
	// pthread_mutex_lock(&data->lock_check);
	if (philo->l_fork->id < philo->r_fork->id)
	{
		pthread_mutex_lock(&philo->l_fork->fork);
		pthread_mutex_lock(&philo->r_fork->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->fork);
		pthread_mutex_lock(&philo->l_fork->fork);
	}
	print_state(TAKE_FORKS, philo, data);
	print_state(TAKE_FORKS, philo, data);
	// pthread_mutex_unlock(&data->lock_check);
	print_state(EATING, philo, data);
	ft_usleep(data->eat_time);
	///////////
	// pthread_mutex_lock(&data->lock_check);
	if (philo->l_fork->id < philo->r_fork->id)
	{
		pthread_mutex_unlock(&philo->r_fork->fork);
		pthread_mutex_unlock(&philo->l_fork->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->l_fork->fork);
		pthread_mutex_unlock(&philo->r_fork->fork);
	}
	// pthread_mutex_unlock(&data->lock_check);
	pthread_mutex_lock(&philo->lock);
	///////////
	philo->meals_num--;
	philo->last_meal = get_time();
	if (philo->meals_num == 0)
		philo->state = 1;
	pthread_mutex_unlock(&philo->lock);
}

void	sleeping(t_philo *philo, t_data *data)
{
	// usleep(1);
	pthread_mutex_lock(&data->lock_end);
	pthread_mutex_lock(&philo->lock_2);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&philo->lock_2);
		pthread_mutex_unlock(&data->lock_end);
		return ;
	}
	pthread_mutex_unlock(&philo->lock_2);
	pthread_mutex_unlock(&data->lock_end);
	// printf("sleeping ");
	// pthread_mutex_lock(&data->lock_check);
	if (check_state(data, philo))
		return ;
	// pthread_mutex_unlock(&data->lock_check);
	// pthread_mutex_lock(&data->lock_print);
	print_state(SLEEPING, philo, data);
	// pthread_mutex_unlock(&data->lock_print);
	ft_usleep(data->sleep_time);
	// pthread_mutex_lock(&data->lock_print);
	// pthread_mutex_unlock(&data->lock_print);
	// pthread_mutex_lock(&philo->lock_2);
	pthread_mutex_lock(&data->lock_end);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&data->lock_end);
		// pthread_mutex_unlock(&philo->lock_2);
		return ;
	}
	// pthread_mutex_unlock(&philo->lock_2);
	pthread_mutex_unlock(&data->lock_end);
	// ft_usleep(1);
	print_state(THINKING, philo, data);
}

// static	void	exit_th(t_data *data)
// {
// 	static	int	i = -1;

// 	while (++i < data->philo_num)
// 	{
// 		// pthread_mutex_destroy(&data->forks[i].fork);
// 		// pthread_mutex_destroy(&data->philos[i].lock);
// 		// pthread_mutex_destroy(&data->philos[i].lock_2);
// 		// pthread_mutex_destroy(&data->philos[i].check_lock);
// 	}
// 	exit (0);
// }

void	*routine(void *dt)
{
	t_philo	*philo;
	//int		flag;
	// Debug i 
	//int		i = 0;
	t_data	*data;

	philo = (t_philo *)dt;
	data = philo->data;
	//flag = 0;
	// pthread_mutex_lock(&philo->lock);
	philo->last_meal = data->sim_start;
	// pthread_mutex_unlock(&philo->lock);
	while (data->end != 1 && philo->state != 1)
	{
		// if (flag == 1)
		// 	pthread_mutex_unlock(&data->lock_end);
		pthread_mutex_lock(&data->lock_end);
		ft_usleep(1);
		eating(philo, data);
		if (data->end == 1)
			return (NULL);
		pthread_mutex_unlock(&data->lock_end);
		// ft_usleep(1);
		pthread_mutex_lock(&data->lock_end);
		if (data->end == 1)
			return (NULL);
		pthread_mutex_unlock(&data->lock_end);
		sleeping(philo, data);
		ft_usleep(1);
		// pthread_mutex_lock(&data->lock_end);
		//flag = 1;
	}
	return (NULL);
}

static	void	*routine_sv(void *dt)
{
	t_data			*data;
	static int		i;
	
	i = 1;
	data = (t_data *)dt;
	while (1 && data->end != 1)
	{
		ft_usleep(1);
		if (data->philos[i].th_id == 0)
			continue ;
		pthread_mutex_lock(&data->lock_end);
		if ((data->philos[i].meals_num == 0 || data->philos[i].state == 1)
			&& (get_time() - data->philos[i].last_meal) > data->death_time)
		{
			
			data->end = 1;
			pthread_mutex_unlock(&data->lock_end);
			// ft_putstr_len("porca madonna\n");
			pthread_mutex_lock(&data->philos[i].lock);
			print_state(DIED, &data->philos[i], data);
			break ;
			// printf(RED"routine sv %d\n", i);
			pthread_mutex_unlock(&data->philos[i].lock);
		}
		pthread_mutex_unlock(&data->lock_end);
		if (i < data->philo_num)
			i++;
		else
			i = 1;
	}
	return (NULL);
}

int	start_routine(t_data *data)
{
	int	i;

	i = -1;
	data->sim_start = get_time();
	while (++i <= data->philo_num)
	{
		if (i == data->philo_num)
		{
			if (pthread_create(&data->supervisor->sv, NULL, routine_sv, data))
				return (ft_putstr_len("Problems in creating a thread\n"));
		}
		else if (i < data->philo_num && pthread_create(&data->philos[i].th_philo, NULL, routine, &data->philos[i]))
			return (ft_putstr_len("Problems in creating a thread\n"));
	}
	i = -1;
	while (++i < data->philo_num)
	{
		//printf("start routine join %d\n", i);
		if (pthread_join(data->philos[i].th_philo, NULL))
			return (ft_putstr_len("Problems in joining a thread\n"));
	}
	exit (0);
	// exit_th(data);
	return (0);
}
