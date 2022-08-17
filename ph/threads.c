#include "philo.h"
#include <sys/time.h>
/*************convertisseur de temps en ms :D********** */
long long	time_in_ms(struct timeval	time)
{
	long long	i;

	return (i = time.tv_sec * 1000 + time.tv_usec * 0.001);
}


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
 
 /*************Mon routine******************************/
void	*routine(void	*args)
{
	t_philo	*philos;
	struct	timeval	end;
	struct	timeval	feat;

	feat.tv_sec = 0;
	feat.tv_usec = 0;
	philos = (t_philo *)args;
	while (*(philos->etat) == 0)
	{
		pthread_mutex_lock(&(philos->mutex[philos->position]));
		pthread_mutex_lock(&(philos->mutex[(philos->position + 1) % philos->nbr_philo]));
		gettimeofday(&end, NULL);
		if ((time_in_ms(end) - time_in_ms(feat)) >= philos->time_to_die)
		{
			*(philos->etat) = 1;
			printf("%lld  %d is dead XD\n", time_in_ms(end) - time_in_ms(*(philos->start)), philos->position + 1);
			return (0);
		}
		printf("%d\n", *(philos->etat));
		printf("%lld  %d has taken a fork\n", time_in_ms(end) - time_in_ms(*(philos->start)), philos->position + 1);
		gettimeofday(&end, NULL);
		printf("%lld  %d is eating\n", time_in_ms(end) - time_in_ms(*(philos->start)), philos->position + 1);
		usleep(philos->time_to_eat * 1000);
		pthread_mutex_unlock(&(philos->mutex[philos->position]));
		pthread_mutex_unlock(&(philos->mutex[(philos->position + 1) % philos->nbr_philo]));
		printf("%lld  %d stop eating\n", time_in_ms(feat) - time_in_ms(*(philos->start)), philos->position + 1);
		gettimeofday(&feat, NULL);
		printf("%lld  %d is sleeping\n", time_in_ms(feat) - time_in_ms(*(philos->start)), philos->position + 1); 
		usleep(philos->time_to_sleep * 1000);
		gettimeofday(&end, NULL);
		printf("%lld  %d is thinking\n", time_in_ms(end) - time_in_ms(*(philos->start)),philos->position + 1);
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

/***********remplissage de  mutexes data *****************/
void	preparation_donnee(t_philo *tab, t_args data)
{
	int	i;
	pthread_mutex_t	*mtx;
	struct timeval	*time;
	int				*etat;

	mtx = creat_mutexes(data);
	time = malloc(sizeof(struct timeval));
	etat = malloc(sizeof(int));
	i = 0;
	while (i < data.nbr_philo)
	{
		tab[i].mutex = mtx; /*giving adress to all your mutex*/
		tab[i].nbr_philo = data.nbr_philo;
		tab[i].time_to_die = data.time_to_die;
		tab[i].time_to_eat = data.time_to_eat;
		tab[i].time_to_sleep = data.time_to_sleep;
		tab[i].start = time;
		tab[i].etat = etat;
		i++;
	}
	*etat = 0;
	gettimeofday(time,	NULL);
}

/*****************Gestion des philosophers***************/
int	philosophers(t_args *data)
{
	t_philo			*tab;

	tab = (t_philo *)malloc(data->nbr_philo * sizeof(t_philo));
	preparation_donnee(tab, *data);
	if (creat_threads(0, tab, *data) != 0)// paire thread 
		return (1);
	if (creat_threads(1, tab, *data) != 0)// impaire thread
		return (2);
	if (join_threads(tab, *data) != 0)
		return (3);
	return (0);
}