/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:50:05 by mapichec          #+#    #+#             */
/*   Updated: 2024/11/12 17:02:26 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
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
#define MAX_PHILOS 200
#define MAX_FORKS 200

typedef struct s_data		t_data;

typedef struct s_forks
{
	pthread_mutex_t			fork;
	int						id;
}				t_forks;

typedef struct s_philo
{
	t_data					*data;
	unsigned long			eat_time;
	unsigned long			last_meal;
	unsigned long			sleep_time;
	int						meals_num;
	int						state;
	int						th_id;
	pthread_t				th_philo;
	t_forks					*r_fork;
	t_forks					*l_fork;
	pthread_mutex_t			lock;
	pthread_mutex_t			lock_2;
	pthread_mutex_t			check_lock;
}			t_philo;

typedef struct s_visor
{
	t_data					*data;
	pthread_t				sv;
}				t_visor;

//TODO: aggiungere un mutex per stampa e general lock
typedef struct s_data
{
	int						philo_num;
	int						end;
	int						meals_num;
	unsigned long			sim_start;
	unsigned long			death_time;
	unsigned long			eat_time;
	unsigned long			sleep_time;
	t_visor					supervisor[0];
	t_philo					philos[MAX_PHILOS];
	t_forks					forks[MAX_FORKS];
	pthread_mutex_t			lock_end;
	pthread_mutex_t			lock_print;
	pthread_mutex_t			lock_check;
}			t_data;

// checks & init
long long		ft_atol(const char *str);
int				ft_atoi(const char *str);
int				ft_str_isdigit(char *str);
int				check_args(char **av, int ac, t_data *data);
unsigned long	get_time(void);
int				print_state(char *str, t_philo *philo, t_data *data);
int				init_ph_fk(t_data *data);
int				ft_usleep(unsigned long time);
int				ft_putnbr_len(int n);
unsigned long	ft_unsigned_l(unsigned long nbr);
int				ft_putchar_len(int c);
int				start_routine(t_data *data);
int				ft_putstr_len(char *str);
