/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:06:21 by jchennak          #+#    #+#             */
/*   Updated: 2022/08/22 15:55:54 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
/*************convertisseur de temps en ms :D********** */
long long	time_in_ms(t_time	time)
{
	long long	i;

	return (i = time.tv_sec * 1000 + time.tv_usec * 0.001);
}


/*************creating mutexes************/
pthread_mutex_t	*creat_mutexes(t_args data)
{
	pthread_mutex_t *mutex;
	int				i;
	
	mutex = malloc(sizeof(pthread_mutex_t) * data.nbr_philo); //  tkayssi a jawaher XD
	if(!mutex)
		return (NULL);
	i = 0;
	while(i < data.nbr_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

/****************affichage des information avec mutexes *********/
void print_action(char *str, t_philo	data, int	suspend)
{
	t_time	end;
	
	if (suspend != 0)
		usleep(suspend * 1000);
	pthread_mutex_lock(&(data.info->mtx));
	gettimeofday(&end, 	NULL);
	printf("%lld %d %s\n", (time_in_ms(end) - time_in_ms(*(data.start))), data.position + 1, str);
	pthread_mutex_unlock(&(data.info->mtx));
}

 /*************Mon routine******************************/
void	*routine(void	*args)
{
	t_philo	*philos;
//	t_time	end;
	philos = (t_philo *)args;
	int	i;
	
	i = 0;
	
	while (1)
	{
		pthread_mutex_lock(&(philos->mutex[philos->position]));
		//********************************
		print_action("has taken a RIGHT fork", *philos, 0);
		// gettimeofday(&end, NULL);
		// pthread_mutex_lock(&(philos->info->mtx));
		// printf("%lld %d has taken a RIGHT fork\n", time_in_ms(end) - time_in_ms(*(philos->start)), philos->position + 1);
		// pthread_mutex_unlock(&(philos->info->mtx));
		//****************************************
		pthread_mutex_lock(&(philos->mutex[(philos->position + 1) % philos->info->nbr_philo]));
		//*************************************
		print_action("has taken a LEFT fork", *philos, 0);
		// gettimeofday(&end, NULL);
		// pthread_mutex_lock(&(philos->info->mtx));
		// printf("%lld %d has taken a LEFT fork\n", time_in_ms(end) - time_in_ms(*(philos->start)), philos->position + 1);
		// pthread_mutex_unlock(&(philos->info->mtx));
		//**************************************
		print_action("is eating", *philos, 0);
		// gettimeofday(&end, NULL);
		// pthread_mutex_lock(&(philos->info->mtx));
		// printf("%lld %d is eating\n", time_in_ms(end) - time_in_ms(*(philos->start)), philos->position + 1);
		// pthread_mutex_unlock(&(philos->info->mtx));
		//*******************************************
		usleep(philos->info->time_to_eat * 1000);
		pthread_mutex_unlock(&(philos->mutex[philos->position]));
		pthread_mutex_unlock(&(philos->mutex[(philos->position + 1) % philos->info->nbr_philo]));
		print_action("is sleeping", *philos, philos->info->time_to_sleep);
		print_action("is thinking", *philos, 0);
	}
	return (0);	
}

/***************creating threads**********************/
int	creat_threads(int i, t_philo *tab, t_args data)
{
	while (i < data.nbr_philo)
	{
		tab[i].position = i;
		if (pthread_create(&(tab[i].tr), NULL, &routine, &tab[i]) != 0)//arguments // n'oublier pas de proteger cette fonction :D // je doit envoyer a chaque fois la case de  thread qui le corresponde :D
			return (write(2, "ERROR : CREAT THREAD :D\n", 24));
		i += 2;
	}
	return (0);
}

/************join_all_mutexes***************************/
int detach_threads(t_philo *tab, t_args data)
{
	int i;

	i = 0;
	while (i < data.nbr_philo)
	{
		if (pthread_join(tab[i].tr, NULL) != 0)// see arguments // n'oubier pas  la protectionq
			return (write(2, "ERROR : JOIN THREAD :D\n", 24));
		i++;
	}
	return (0);
}


/************destroy all mutexes***************************/
void destroy_all(pthread_mutex_t *tab, int nbr)
{
	int	i;
		
	i = 0;
	while(i < nbr)
	{
		pthread_mutex_destroy(&tab[i]);
		i++;
	}
}

/***********remplissage de  mutexes data *****************/
void	preparation_donnee(t_philo *tab, t_args *data)
{
	int	i;
	pthread_mutex_t	*mtx;
	t_time			*time;
	//int				*etat;

	pthread_mutex_init(&(data->mtx), NULL);
	mtx = creat_mutexes(*data);
	time = malloc(sizeof(struct timeval));
	//etat = malloc(sizeof(int));
	i = 0;
	while (i < data->nbr_philo)
	{
		tab[i].mutex = mtx; /*giving adress to all your mutex*/
		tab[i].info = data;
		tab[i].start = time;
	//	tab[i].etat = etat;
		i++;
	}
	//*etat = 0;
	gettimeofday(time,	NULL);
}

/*****************Gestion des philosophers***************/
int	philosophers(t_args *data)
{
	t_philo			*tab;

	tab = (t_philo *)malloc(data->nbr_philo * sizeof(t_philo));
	preparation_donnee(tab, data);
	if (creat_threads(0, tab, *data) != 0)// paire thread 
		return (1);
	usleep(data->nbr_philo * 0.6);
	if (creat_threads(1, tab, *data) != 0)// impaire thread
		return (2);
	if (detach_threads(tab, *data) != 0)// detach all the threads and remove the waiting so you can surpervisee the threads
		return (3);
	pthread_mutex_destroy(&(data->mtx));
	destroy_all(tab->mutex, data->nbr_philo);
	return (0);
}

