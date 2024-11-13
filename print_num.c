/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:22:53 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/12 18:09:28 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putnbr_len(int n)
{
	int	len;

	len = 0;
	if (n > 9)
		ft_putnbr_len(n / 10);
	ft_putchar_len((n % 10) + 48);
	return (len);
}

unsigned long	ft_unsigned_l(unsigned long nbr)
{
	long	len;

	len = 0;
	if (nbr >= 10)
		ft_unsigned_l(nbr / 10);
	ft_putchar_len((nbr % 10) + 48);
	return (len);
}

int	ft_putchar_len(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		i += write(1, "(null)", 6);
		return (i);
	}
	while (str[i])
	{
		ft_putchar_len(str[i]);
		i++;
	}
	return (i);
}

int	print_state(char *str, t_philo *philo, t_data *data)
{
	unsigned long	time;

	
	pthread_mutex_lock(&data->lock_print);
	if (philo->th_id == 0)
		return (ft_putstr_len("coglione\n"));
	// printf(RED"ciao %lu\nciao %lu\n"RESET, data->eat_time, philo->eat_time);
	ft_usleep(1);
	time = get_time() - data->sim_start;
	ft_unsigned_l(time);
	ft_putchar_len(' ');
	ft_putnbr_len(philo->th_id);
	ft_putchar_len(' ');
	ft_putstr_len(str);
	ft_putchar_len('\n');
	pthread_mutex_unlock(&data->lock_print);
	return (0);
}
