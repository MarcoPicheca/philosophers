/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:56:18 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/14 18:11:06 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_state(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->lock_check);
	if ((get_time() - philo->last_meal) > data->death_time)
	{
		pthread_mutex_lock(&data->lock_end);
		ft_putstr_len(GREEN"porco cane\n"RESET"");
		data->end = 1;
		pthread_mutex_unlock(&data->lock_end);
		print_state(DIED, philo, data);
		pthread_mutex_unlock(&data->lock_check);
		return (1);
	}
	pthread_mutex_unlock(&data->lock_check);
	return (0);
}

void	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->lock_end);
	if (data->end == 1 || philo->state == 1)
	{
		pthread_mutex_unlock(&data->lock_end);
		return ;
	}
	pthread_mutex_unlock(&data->lock_end);
	if (check_state(data, philo))
		return ;
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
	print_state(EATING, philo, data);
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(data->eat_time);
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
	pthread_mutex_lock(&philo->lock);
	philo->meals_num--;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(&philo->lock);
	if (philo->meals_num == 0)
		philo->state = 1;
	pthread_mutex_unlock(&philo->lock);
}

void	sleeping(t_philo *philo, t_data *data)
{
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
	if (check_state(data, philo))
		return ;
	print_state(SLEEPING, philo, data);
	ft_usleep(data->sleep_time);
	pthread_mutex_lock(&data->lock_end);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&data->lock_end);
		return ;
	}
	pthread_mutex_unlock(&data->lock_end);
	print_state(THINKING, philo, data);
}

void	*routine(void *dt)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)dt;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->lock_end);
		if (data->end == 1 || philo->state == 1)
		{
			pthread_mutex_unlock(&data->lock_end);
			return (NULL);
		}
		pthread_mutex_unlock(&data->lock_end);
		eating(philo, data);
		// usleep(1);
		pthread_mutex_lock(&data->lock_end);
		if (data->end == 1 || philo->state == 1)
		{
			pthread_mutex_unlock(&data->lock_end);
			return (NULL);
		}
		pthread_mutex_unlock(&data->lock_end);
		pthread_mutex_lock(&data->lock_end);
		if (data->end == 1 || philo->state == 1)
		{
			pthread_mutex_unlock(&data->lock_end);
			return (NULL);
		}
		pthread_mutex_unlock(&data->lock_end);
		sleeping(philo, data);
		// ft_usleep(1);
	}
	return (NULL);
}

static	void	*routine_sv(void *dt)
{
	t_data			*data;
	static int		i;
	
	i = 1;
	data = (t_data *)dt;
	while (1)
	{
		usleep(5);
		pthread_mutex_lock(&data->lock_end);
		if (data->philos[i].th_id == 0)
			i = 1;
		pthread_mutex_unlock(&data->lock_end);
		pthread_mutex_lock(&data->lock_end);
		if (data->end == 1)
			return (NULL);
		pthread_mutex_unlock(&data->lock_end);
		pthread_mutex_lock(&data->philos[i].lock);
		if (data->philos[i].meals_num == 0)
		{
			// ft_putstr_len(GREEN"sono qui"RESET"");
			// ft_putnbr_len(data->philos[i].th_id);
			// ft_putchar_len('\n');
			data->philos[i].state = 1;
			pthread_mutex_unlock(&data->philos[i].lock);
			return (NULL);
			// pthread_mutex_lock(&data->lock_end);
			// pthread_mutex_unlock(&data->lock_end);
			// ft_putstr_len(CYAN"porca madonna\n");
		}
		pthread_mutex_unlock(&data->philos[i].lock);
		pthread_mutex_lock(&data->philos[i].lock);
		pthread_mutex_lock(&data->lock_end);
		if ((get_time() - data->philos[i].last_meal) > data->death_time)
		{
			data->end = 1;
			ft_putstr_len(GREEN"porco dio\n"RESET"");
			pthread_mutex_unlock(&data->lock_end);
			print_state(DIED, &data->philos[i], data);
			pthread_mutex_unlock(&data->philos[i].lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->lock_end);
		pthread_mutex_unlock(&data->philos[i].lock);
		if (i < data->philo_num)
			i++;
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
		data->philos[i].last_meal = data->sim_start;
		if (i == data->philo_num)
		{
			if (pthread_create(&data->supervisor[0].sv, NULL, routine_sv, data))
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
	// ft_putstr_len(GREEN"sono qua\n");
	if (pthread_join(data->supervisor[0].sv, NULL))
		return (ft_putstr_len("Problems in joining a thread\n"));
	exit (0);
	// exit_th(data);
	return (0);
}
