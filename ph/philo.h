/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:49:32 by jchennak          #+#    #+#             */
/*   Updated: 2022/08/24 01:29:02 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h> 
# include <sys/time.h>

typedef struct timeval	t_time;

typedef struct s_args
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				life_cercle;
	pthread_mutex_t	mtx;
}	t_args;

typedef struct s_philo
{
	int				position;
	pthread_mutex_t	meals;
	pthread_mutex_t	*mutex;
	pthread_t		tr;	
	t_args			*info;
	t_time			start;
	t_time			meal;
	int				nb_meal;
	int				i;		
}	t_philo;

int				ft_atoi(char *str);
int				philosophers(t_args *data);
int				input(char **av, t_args *inp, int argc);
pthread_mutex_t	*creat_mutexes(t_args data);
void			preparation_donnee(t_philo *tab, t_args *data);
long long		time_in_ms(t_time	time);
void			go_to_sleep(int suspend);
void			print_action(char *str, t_philo	data, int suspend);
void			*routine(void	*args);
int				check_all(t_philo *tab, int nb_philos, int time_to_die);
int				if_dead(int i, t_philo *tab, int time_to_die);

#endif
