/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:05:53 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/15 15:17:43 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_args(char **av, int ac, t_data *data)
{
	int	i;

	i = 0;
	memset(data, 0, sizeof(t_data));
	while (++i < ac)
	{
		if (ft_str_isdigit(av[i]))
			return (1);
	}
	data->philo_num = ft_atoi(av[1]);
	data->death_time = (unsigned long)ft_atol(av[2]);
	data->eat_time = (unsigned long)ft_atol(av[3]);
	data->sleep_time = (unsigned long)ft_atol(av[4]);
	data->end = 0;
	if (!av[5])
		data->meals_num = -1;
	else if (av[5])
		data->meals_num = ft_atoi(av[5]);
	if (av[5] && data->meals_num <= 0)
		return (1);
	if (data->philo_num > 200 || data->philo_num < 1 || data->death_time < 60
		|| data->sleep_time < 60 || data->eat_time < 60)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (printf("Problems in args\n"));
	if (check_args(av, ac, &data))
		return (printf("Problems in args\n"));
	if (init_ph_fk(&data))
		return (printf("Problems in init_ph_fk\n"));
	if (start_routine(&data))
		return (1);
	return (0);
}
