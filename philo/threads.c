/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:06:21 by jchennak          #+#    #+#             */
/*   Updated: 2022/08/24 04:09:02 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*************convertisseur de temps en ms :D********** */
long long	time_in_ms(t_time	time)
{
	long long	i;

	return (i = time.tv_sec * 1000 + time.tv_usec * 0.001);
}

/*************correction de usleep ****/
void	go_to_sleep(int suspend)
{
	t_time	start;
	t_time	end;

	gettimeofday(&start, NULL);
	usleep(suspend * 0.9);
	gettimeofday(&end, NULL);
	while ((time_in_ms(end) - time_in_ms(start)) < (suspend * 0.001))
	{
		usleep(50);
		gettimeofday(&end, NULL);
	}
}

/*************creating mutexes************/
pthread_mutex_t	*creat_mutexes(t_args data)
{
	pthread_mutex_t	*mutex;
	int				i;

	mutex = malloc(sizeof(pthread_mutex_t) * data.nbr_philo);
	if (!mutex)
		return (NULL);
	i = 0;
	while (i < data.nbr_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

/****************affichage des information avec mutexes *********/
void	print_action(char *str, t_philo	data, int suspend)
{
	t_time	end;

	if (suspend != 0)
		go_to_sleep(suspend * 1000);
	pthread_mutex_lock(&(data.info->mtx));
	gettimeofday(&end, NULL);
	printf("%lld %d %s\n", (time_in_ms(end) - time_in_ms(data.start)),
		data.position + 1, str);
	pthread_mutex_unlock(&(data.info->mtx));
}

/*************Mon routine******************************/
void	*routine(void	*args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&(philos->mutex[philos->position]));
		print_action("has taken a fork", *philos, 0);
		pthread_mutex_lock(&(philos->mutex[(philos->position + 1)
				% philos->info->nbr_philo]));
		print_action("has taken a fork", *philos, 0);
		pthread_mutex_lock(&philos->meals);
		gettimeofday(&(philos->meal), NULL);
		pthread_mutex_unlock(&philos->meals);
		print_action("is eating", *philos, 0);
		go_to_sleep(philos->info->time_to_eat * 1000);
		pthread_mutex_lock(&philos->meals);
		philos->nb_meal++;
		pthread_mutex_unlock(&philos->meals);
		pthread_mutex_unlock(&(philos->mutex[(philos->position + 1)
				% philos->info->nbr_philo]));
		pthread_mutex_unlock(&(philos->mutex[philos->position]));
		print_action("is sleeping", *philos, philos->info->time_to_sleep);
		print_action("is thinking", *philos, 0);
	}
}
