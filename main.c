/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:11:40 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/06 13:10:00 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

// TODO: check_args max 200 philos min 1

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
	data->philo_num = ft_atoi(av[1]) + 1;
	data->death_time = (unsigned long)ft_atol(av[2]);
	data->eat_time = (unsigned long)ft_atol(av[3]);
	data->sleep_time = (unsigned long)ft_atol(av[4]);
	if (!av[5])
		data->meals_num = -1;
	else if (av[5])
		data->meals_num = ft_atoi(av[5]);
	if (data->philo_num > 200 || data->philo_num < 1)
		return (1);
	// Debug
	// printf("%lu d_time\n%lu eat_time\n%lu sleep_time\n%lu sim_start\n",
	// data->death_time, data->eat_time, data->sleep_time, data->sim_start);
	return (0);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_in);
	if (philo->last_meal)
		philo->last_meal = philo->curr_meal;
	else if (philo->last_meal == 0)
		philo->last_meal = get_time() - philo->data->sim_start;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	// printf(RED"philo %d meals %d\n"RESET, philo->th_id, philo->meals_num);
	print_state(EATING, philo, 1);
	ft_usleep(philo->data->eat_time);
	pthread_mutex_lock(&philo->lock);
	philo->curr_meal = get_time() - philo->data->sim_start;
	philo->meals_num--;
	if ((philo->curr_meal - philo->last_meal) >= philo->death_time)
		philo->state = 1;
	if (philo->meals_num == 0)
		philo->state = 2;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->death_time = (get_time() - philo->data->sim_start) + philo->data->death_time;
	pthread_mutex_unlock(&philo->data->lock_in);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_in);
	print_state(SLEEPING, philo, 2);
	ft_usleep(philo->data->sleep_time);
	pthread_mutex_unlock(&philo->data->lock_in);
}

static void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_in);
	print_state(THINKING, philo, 3);
	ft_usleep(1);
	pthread_mutex_unlock(&philo->data->lock_in);
}

// routine
void	*routine(void *th)
{
	t_data	*data;
	t_philo	*philos;

	philos = (t_philo *)th;
	data = (t_data *)philos->data;
	// printf(GREEN"%d %d\n"RESET, philos->th_id, philos->meals_num);
	// pthread_mutex_lock(&data->lock_in);
	while (philos->state != 1 && philos->state != 2
		&& philos->meals_num != 0 && data->end == 0)
	{
		eating(philos);
		sleeping(philos);
		thinking(philos);
		ft_usleep(1);
	}
	// pthread_mutex_unlock(&data->lock_in);
	return (NULL);
}

/*
	l'utimo filosofo dovra' prendere la fork[0] a sx e fork[philos num] a dx
*/
int init_forks(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->lock_in, NULL))
		return (printf(RED"Mutex lock in error\n"RESET), 1);
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf(RED"Mutex error\n"RESET), 1);
		i++;
	}
	i = 0;
    while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->philos[i].lock, NULL))
			return (printf(RED"Mutex error\n"RESET), 1);
		memset(&data->philos[i], 0, sizeof(t_philo));
		data->philos[i].data = data;
		data->philos[i].meals_num = data->meals_num;
		data->philos[i].th_id = i + 1;
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].l_fork = &data->forks[(i + 1) % data->philo_num];
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	sv;
	int	i;

	i = 0;	
	sv = data->philo_num;
	data->sim_start = get_time();
	while (i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].death_time = data->death_time;
		data->philos[i].eat_time = data->eat_time;
		data->philos[i].sleep_time = data->sleep_time;
		if (pthread_create(&data->philos[i].th_philo, NULL, routine, &data->philos[i]))
			return (printf("Errore create\n"), 1);
		i++;
	}
	if (i == data->philo_num
		&& pthread_create(&data->philos[sv].th_philo, NULL, &routine_sv, data))
		return (printf("Errore supervisor\n"), 1);
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->philos[i].th_philo, NULL))
			return (printf("Problems in join\n"), 1);
		i++;
	}
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
		return (printf(RED"problems in av\n"RESET), 1);
	if (check_args(av, ac, &data))
		return (printf(RED"problems in av\n"RESET), 1);
	if (init_forks(&data))
		return (1);
	if (init_philos(&data))
		return (1);
	if (data.end == 1)
		ft_exit_rt(&data);
	return (0);
}