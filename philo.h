/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:50:05 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/04 20:28:21 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H
#endif
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/time.h>
#include <stddef.h>

// Colors for print
#define RESET		"\x1b[0m"	// Reset colore
#define BLACK		"\x1b[30m"	// Nero
#define RED			"\x1b[31m"	// Rosso
#define GREEN		"\x1b[32m"	// Verde
#define YELLOW		"\x1b[33m"	// Giallo
#define BLUE		"\x1b[34m"	// Blu
#define MAGENTA		"\x1b[35m"	// Magenta
#define CYAN		"\x1b[36m"	// Ciano
#define WHITE		"\x1b[37m"	// Bianco

// Print messages
#define TAKE_FORKS	"has taken a fork"
#define THINKING	"is thinking"
#define SLEEPING	"is sleeping"
#define EATING		"is eating"
#define DIED		"died"
#define MAX_PHILOS 250
#define MAX_FORKS 250

typedef struct s_philo
{
	unsigned long			death_time;
	unsigned long			eat_time;
	unsigned long			sleep_time;
	unsigned long			meals_num;
	bool					think_state;
	int						th_id;
	pthread_t				th_philo;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			lock;
}			t_philo;

//TODO: aggiungere un mutex per stampa e general lock
typedef struct s_data
{
	int						philo_num;
	int						meals_num;
	unsigned long			sim_start;
	unsigned long			death_time;
	unsigned long			eat_time;
	unsigned long			sleep_time;
	t_philo					philos[MAX_PHILOS];
	pthread_t				*th;
	pthread_mutex_t			forks[MAX_FORKS];
	// TODO: da vedere se utile
	// pthread_mutex_t			lock_in;
}			t_data;

// checks & init
long long	ft_atol(const char *str);
int			ft_atoi(const char *str);
int			ft_str_isdigit(char *str);
int			check_args(char **av, int ac, t_data *data);
void		*routine(void *th);
int			init_data(t_data *data);