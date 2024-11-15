/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:10:01 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/15 18:13:32 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned	long	get_time(void)
{
	struct timeval	tv;
	unsigned long	res;

	res = 0;
	if (gettimeofday(&tv, NULL))
		return (printf("Error gettimeofday()\n"), 0);
	res = (tv.tv_sec * (unsigned long)1000) + (tv.tv_usec / 1000);
	return (res);
}

int	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(100);
	return (0);
}

long long	ft_atol(const char *str)
{
	long long	sign;
	long long	i;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (sign * res);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	segno;

	i = 0;
	result = 0;
	segno = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			segno *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * segno);
}

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}
