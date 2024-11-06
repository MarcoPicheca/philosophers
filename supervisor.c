/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:09:18 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/06 12:58:31 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit_rt(t_data *data)
{
	int	i = 0;

	pthread_mutex_lock(&data->lock_in);
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		data->philos[i].l_fork = NULL;
		data->philos[i].r_fork = NULL;
		i++;
	}
	pthread_mutex_unlock(&data->lock_in);
	exit(0);
	// pthread_mutex_destroy(&data->lock_in);
}

/*
	ROUTINE SUPERVISOR
	- a philosoph is dead; dead_state == 1
	- a philosoph has finished to eat his meals; state == 2
*/
void	*routine_sv(void *sv)
{
	int		i;
	t_philo	*super_v;
	t_philo	*philos;
	t_data	*data;
	
	data = (t_data *)sv;
	super_v = &data->philos[data->philo_num];
	philos = (t_philo *)data->philos;
	i = 0;
	while (1)
	{
		// printf("routine_sv\n");
		while (i < data->philo_num)
		{


			pthread_mutex_lock(&data->lock_in);
			if (data->philos[i].state == 1 || data->philos[i].state == 2
				|| (data->philos[i].curr_meal - data->philos[i].last_meal) >= data->philos[i].death_time)
			{
				printf("%lu dead time\n", (data->philos[i].curr_meal - data->philos[i].last_meal));
				print_state(DIED, &data->philos[i], 4);
				data->end = 1;
			}
			// if (philos[i].meals_num == 0)
			// {
			// 	philos[i].state = 2;
			// }
			pthread_mutex_unlock(&data->lock_in);
			ft_usleep(1);
			// pthread_mutex_lock(&data->philos[i].lock);
			i++;
		}
		i = 0;
	}
	return (NULL);
}

// 1 eat; 2 sleep; 3 think; 4 dead

int	print_state(char *str, t_philo *philo, int state)
{
	unsigned long	time;

	// pthread_mutex_lock(&philo->lock);

	/**if x = 0 */
	if (state == 1)
	{
		time = get_time() - philo->data->sim_start;
		printf(YELLOW);
	}
	if (state == 2)
	{
		time = get_time() - philo->data->sim_start;
		printf(CYAN);
	}
	if (state == 3)
	{
		time = get_time() - philo->data->sim_start;
		printf(GREEN);
	}
	if (state == 4)
	{
		time = get_time() - philo->data->sim_start;
		printf(RED);
	}
	// printf(GREEN"%d in print\n"RESET, philo->th_id);
	ft_usleep(1);
	printf("%lu %i %s\n"RESET, time, philo->th_id, str);
	// pthread_mutex_unlock(&philo->lock);
	return (0);
}

			// pthread_mutex_lock(&data->philos[i].lock);
			// printf(GREEN"%d %d\n"RESET, data->philos[i].th_id, data->philos[i].meals_num);
			// printf(RED"%lu d_time\n%lu get_time()\n"RESET, data->philos[i].death_time, get_time());
			/**
			 *  start_simulation
			 * 	time lastmeal
			 * 	now
			 * 

			 * 	res = time_last - start_simulation   (13.00 , 12.00 , 1h)
			 	if(res > philo.tiumetodie)
				{
					mutex lock
					variabile x = 1;
					mutex unlock
					muore e fermo la simulazione
					


				}
			 
			 * 
			 * 
			 * 
			 */