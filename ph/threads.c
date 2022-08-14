#include "philo.h"
/*************creating mutexes************/
pthread_mutex_t	*creat_mutexes(t_args data)
{
	pthread_mutex_t *mutex;
	int				i;
	mutex = malloc(sizeof(pthread_mutex_t));
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

void	*routine(void	*args)
{
	t_philo	*philos;
	/******pense a faire une mutex pour les print :D*********/
	philos = (t_philo *)args;
	pthread_mutex_lock(&(philos->mutex[philos->position]));
	pthread_mutex_lock(&(philos->mutex[(philos->position + 1) % philos->nbr_philo]));
	printf("thread %d is eating :D\n", philos->position);
	pthread_mutex_unlock(&(philos->mutex[philos->position]));
	pthread_mutex_unlock(&(philos->mutex[(philos->position + 1) % philos->nbr_philo]));
	printf("thread %d is sleeping:D\n", philos->position);  
	printf("thread %d is thinking :D \n", philos->position);
	usleep(1000000);
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
int join_threads(t_philo *tab, t_args data)
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

int	philosophers(t_args *data)
{
	t_philo			*tab;
	pthread_mutex_t	*mtx;
	int				i;

	tab = (t_philo *)malloc(data->nbr_philo * sizeof(t_philo));
	mtx = creat_mutexes(*data);
	i = 0;
	while (i < data->nbr_philo)
	{
		tab[i].mutex = mtx; /*giving adress to all your mutex*/
		tab[i].nbr_philo = data->nbr_philo;
		tab[i].time_to_die = data->time_to_die;
		tab[i].time_to_eat = data->time_to_eat;
		tab[i].time_to_sleep = data->time_to_sleep;
		i++;
	}
	if (creat_threads(0, tab, *data) != 0)
		return (1);
	if (creat_threads(1, tab, *data) != 0)
		return (2);
	if (join_threads(tab, *data) != 0)
		return (3);
	return (0);
}