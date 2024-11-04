/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:11:40 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/04 20:31:02 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_args(char **av, int ac, t_data *data)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_str_isdigit(av[i]))
			return (1);
		i++;
	}
	data->philo_num = ft_atoi(av[1]);
	data->death_time = (unsigned long)ft_atol(av[2]);
	data->eat_time = (unsigned long)ft_atol(av[3]);
	data->sleep_time = (unsigned long)ft_atol(av[4]);
	if (!av[5])
		data->meals_num = -1;
	else if (av[5])
		data->meals_num = ft_atoi(av[5]);
	return (0);
}
// routine
void	*routine(void *th)
{
	t_data	*data;

	data = (t_data *)th;
	/*
		eat()
		sleep()
		think()
	*/
	return (NULL);
}

/*
	l'utimo filosofo dovra' prendere la fork[0] a sx e fork[philos num] a dx
*/
// TODO: gestire caso con un solo filosofo perche' la simulazione deve partire comunque
int init_data(t_data *data)
{
	int	i;
	pthread_mutex_t *left;
	pthread_mutex_t *right;

	i = -1;
	while (++i < data->philo_num)
		pthread_mutex_init(&data->forks[i], NULL);
	printf(RED"%d FORKS\n"RESET, i);
	i = -1;
    while (++i < data->philo_num)
	{
		data->philos[i].th_id = i + 1;
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[(i + 1) % data->philo_num];
	}
	i = -1;
	while (++i < data->philo_num)
	{
		right = data->philos[i].r_fork;
		left = data->philos[i].l_fork;
		printf("Philosopher %d has right fork %p and left fork %p\n", 
		data->philos[i].th_id, right, left);		
	}
	exit (0);
	return (0);
}

/*
	- [av 1] philos_num
	- [av 2] time to die
	- [av 3] time to eat
	- [av 4] time to sleep
	- [av 5] number of meals
*/

int main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (!av || ac < 5 || ac > 6)
		return (0);
	if (check_args(av, ac, &data))
		return (printf(RED"problems in av\n"RESET));
	if (init_data(&data))
	return (0);
}