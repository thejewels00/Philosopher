/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 16:49:32 by jchennak          #+#    #+#             */
/*   Updated: 2022/08/17 15:53:33 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h> // remove it :D
#include <sys/time.h>

typedef struct s_args
{
	int	nbr_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	life_cercle;
}	t_args;

typedef	struct s_philo
{
	int	position;
	pthread_mutex_t	*mutex; // je vas cree une adresse ou tout les  threads acceder a ce tableau :)
	pthread_t		tr;
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*etat;
	struct timeval	*start;
		
}	t_philo;

int				ft_atoi(char *str);
int				philosophers(t_args *data);
int				input(char **av, t_args *inp, int argc);
pthread_mutex_t	*creat_mutexes(t_args data);
void	preparation_donnee(t_philo *tab, t_args data);

#endif
