/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 01:01:31 by jchennak          #+#    #+#             */
/*   Updated: 2022/08/24 01:29:51 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/***************creating threads**********************/
int	creat_threads(int i, t_philo *tab, t_args data)
{
	while (i < data.nbr_philo)
	{
		tab[i].position = i;
		if (pthread_create(&(tab[i].tr), NULL, &routine, &tab[i]) != 0)
			return (write(2, "ERROR : CREAT THREAD :D\n", 24));
		if (pthread_detach(tab[i].tr))
			return (write(2, "ERROR : DETACH THREAD :D\n", 24));
		i += 2;
	}
	return (0);
}

/***********remplissage de  mutexes data *****************/
void	preparation_donnee(t_philo *tab, t_args *data)
{
	int				i;
	pthread_mutex_t	*mtx;

	pthread_mutex_init(&(data->mtx), NULL);
	mtx = creat_mutexes(*data);
	i = 0;
	while (i < data->nbr_philo)
	{
		tab[i].mutex = mtx;
		tab[i].info = data;
		gettimeofday(&(tab[i].start), NULL);
		tab[i].meal = tab[i].start;
		pthread_mutex_init(&(tab[i].meals), NULL);
		i++;
	}
}

/************check threads************/
int	check_all(t_philo *tab, int nb_philos, int time_to_die)
{
	int		i;	
	int		count;

	while (1)
	{
		i = -1;
		count = 0;
		pthread_mutex_lock(&(tab[i + 1].info->mtx));
		while (++i < nb_philos)
		{
			pthread_mutex_lock(&(tab[i].meals));
			if (if_dead(i, tab, time_to_die) == 0)
				return (0);
			if ((tab[i].nb_meal >= tab[i].info->life_cercle)
				&& tab[i].info->life_cercle != -2)
				count++;
			pthread_mutex_unlock(&(tab[i].meals));
		}
		if (count == nb_philos)
			return (0);
		pthread_mutex_unlock(&(tab[--i].info->mtx));
		usleep(50);
	}
	return (0);
}

/*****************Gestion des philosophers***************/
int	philosophers(t_args *data)
{
	t_philo			*tab;

	tab = (t_philo *)malloc(data->nbr_philo * sizeof(t_philo));
	preparation_donnee(tab, data);
	if (creat_threads(0, tab, *data) != 0)
		return (1);
	usleep(data->nbr_philo * 50);
	if (creat_threads(1, tab, *data) != 0)
		return (2);
	check_all(tab, data->nbr_philo, data->time_to_die);
	free(tab[0].mutex);
	free(tab);
	return (0);
}

int	if_dead(int i, t_philo *tab, int time_to_die)
{
	t_time	cur;

	gettimeofday(&cur, NULL);
	if ((time_in_ms(cur) - time_in_ms(tab[i].meal)) >= time_to_die)
	{
		printf("%lld %d is died\n", (time_in_ms(cur) \
			- time_in_ms(tab[i].start)), tab[i].position + 1);
		return (0);
	}
	return (1);
}
