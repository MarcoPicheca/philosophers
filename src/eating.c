/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:27:28 by marco             #+#    #+#             */
/*   Updated: 2024/11/19 14:48:40 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static	int	lock_fk_check(t_data *data, t_philo *philo)
{
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
	if (check_end(data, philo))
	{
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
		return (1);
	}
	return (0);
}

static	void	meal_time(t_data *data, t_philo *philo)
{
	print_state(TAKE_FORKS, philo, data);
	print_state(TAKE_FORKS, philo, data);
	pthread_mutex_lock(&philo->lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lock);
	print_state(EATING, philo, data);
	ft_usleep(data->eat_time);
}

void	eating(t_philo *philo, t_data *data)
{
	if (lock_fk_check(data, philo))
		return ;
	meal_time(data, philo);
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
	if (data->meals_num > 0)
	{
		pthread_mutex_lock(&philo->lock);
		philo->meals_num--;
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_lock(&philo->lock);
		if (philo->meals_num == 0)
			philo->state = 1;
		pthread_mutex_unlock(&philo->lock);
	}
}
