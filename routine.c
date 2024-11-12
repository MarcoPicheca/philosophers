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
	usleep(10);
	pthread_mutex_lock(&philo->lock_2);
	if ((get_time() - philo->last_meal) > data->death_time)
	{
		pthread_mutex_lock(&data->lock_end);
		data->end = 1;
		pthread_mutex_unlock(&data->lock_end);
		print_state(DIED, philo, data);
		pthread_mutex_unlock(&philo->lock_2);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock_2);
	return (0);
}

void	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->lock_2);
	// pthread_mutex_lock(&data->lock_in);
	if (data->end == 1)
	{
		// pthread_mutex_unlock(&data->lock_in);
		pthread_mutex_unlock(&philo->lock_2);
		return ;
	}
	pthread_mutex_unlock(&philo->lock_2);
	// pthread_mutex_unlock(&data->lock_in);
	if (check_state(data, philo))
		return ;
	pthread_mutex_lock(&philo->lock_2);
	pthread_mutex_lock(&philo->l_fork->fork);
	print_state(TAKE_FORKS, philo, data);
	// printf(GREEN"eat %lu\neat %lu\neat %d\n"RED, philo->eat_time, philo->sleep_time, philo->meals_num);
	// pthread_mutex_unlock(&data->lock_print);
	pthread_mutex_lock(&philo->r_fork->fork);
	// pthread_mutex_lock(&data->lock_print);
	print_state(TAKE_FORKS, philo, data);
	pthread_mutex_unlock(&philo->lock_2);
	// pthread_mutex_unlock(&data->lock_print);
	// ft_usleep(1);
	// pthread_mutex_lock(&data->lock_print);
	print_state(EATING, philo, data);
	ft_usleep(data->eat_time);
	// pthread_mutex_unlock(&data->lock_print);
	// pthread_mutex_lock(&data->lock_in);
	// pthread_mutex_unlock(&data->lock_in);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
	pthread_mutex_lock(&philo->lock);
	ft_putstr_len("meals ");
	ft_putnbr_len(philo->meals_num);
	ft_putchar_len('\n');
	philo->meals_num--;
	philo->last_meal = get_time();
	if (philo->meals_num == 0)
		philo->state = 1;
	pthread_mutex_unlock(&philo->lock);
	usleep(10);
}

void	sleeping(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->lock_2);
	pthread_mutex_lock(&data->lock_end);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&data->lock_end);
		pthread_mutex_unlock(&philo->lock_2);
		return ;
	}
	pthread_mutex_unlock(&philo->lock_2);
	pthread_mutex_unlock(&data->lock_end);
	if (check_state(data, philo))
		return ;
	// pthread_mutex_lock(&data->lock_print);
	print_state(SLEEPING, philo, data);
	// pthread_mutex_unlock(&data->lock_print);
	ft_usleep(data->sleep_time);
	// pthread_mutex_lock(&data->lock_print);
	print_state(THINKING, philo, data);
	// pthread_mutex_unlock(&data->lock_print);
	usleep(10);
}

static	void	exit_th(t_data *data)
{
	static	int	i = -1;

	while (++i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		pthread_mutex_destroy(&data->philos[i].lock);
		pthread_mutex_destroy(&data->philos[i].check_lock);
	}
	pthread_mutex_destroy(&data->lock_in);
	exit (0);
}

void	*routine(void *dt)
{
	t_philo	*philo;
	int		flag;
	t_data	*data;

	philo = (t_philo *)dt;
	data = philo->data;
	flag = 0;
	// pthread_mutex_lock(&philo->lock);
	philo->last_meal = data->sim_start;
	// pthread_mutex_unlock(&philo->lock);
	while (data->end != 1 && philo->state != 1)
	{
		// if (flag == 1)
		// 	pthread_mutex_unlock(&data->lock_end);
		pthread_mutex_lock(&data->lock_end);
		eating(philo, data);
		if (data->end == 1)
			return (NULL);
		pthread_mutex_unlock(&data->lock_end);
		sleeping(philo, data);
		usleep(10);
		// pthread_mutex_lock(&data->lock_end);
		flag = 1;
	}
	return (NULL);
}

static	void	*routine_sv(void *dt)
{
	t_data			*data;
	static int		i;
	
	i = -1;
	data = (t_data *)dt;
	while (1)
	{
		pthread_mutex_lock(&data->philos[i].lock);
		if (check_state(data, &data->philos[i]))
		{
			pthread_mutex_lock(&data->lock_end);
			data->end = 1;
			pthread_mutex_unlock(&data->lock_end);
		}
		if ((data->philos[i].meals_num == 0 || data->philos[i].state == 1)
			&& (get_time() - data->philos[i].last_meal) > data->death_time)
		{
			
			pthread_mutex_lock(&data->lock_end);
			data->end = 1;
			pthread_mutex_unlock(&data->lock_end);
			// pthread_mutex_lock(&data->lock_print);
			print_state(DIED, &data->philos[i], data);
			// pthread_mutex_unlock(&data->lock_print);
		}
		pthread_mutex_unlock(&data->philos[i].lock);
		if (i == data->philo_num)
			i = 0;
		else
			i++;
		// pthread_mutex_unlock(&&data->lock_sv);
		ft_usleep(2);
	}
	return (NULL);
}

int	start_routine(t_data *data)
{
	int	i;

	i = -1;
	data->sim_start = get_time();
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].th_philo, NULL, routine, &data->philos[i]))
			return (ft_putstr_len("Problems in creating a thread\n"));
	}
	if (i == data->philo_num)
	{
		if (pthread_create(&data->supervisor->sv, NULL, routine_sv, data))
			return (ft_putstr_len("Problems in creating a thread\n"));
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->philos[i].th_philo, NULL))
			return (ft_putstr_len("Problems in jining a thread\n"));
	}
	if (pthread_join(data->supervisor->sv, NULL))
		return (ft_putstr_len("Problems in jining a thread\n"));
	exit_th(data);
	return (0);
}
