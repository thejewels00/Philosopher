#include "philo.h"

void	*routine(void *arg)
{
	t_work	*philos;
	philos = (t_work *)arg;
	//int pos;
	//pos = *(int *)arg;
	printf("philo %d , is eating\n",	*philos->position );
	usleep(50);
	printf("lllphilo %d , is eating\n",	*philos->position );
	return 0;
} 

int	philosophers(t_args *data)
{
	int		i;
	t_work	ph_id;
	
	ph_id.tr = malloc(data->nbr_philo * sizeof(pthread_t));
	ph_id.mt = malloc(data->nbr_philo * sizeof(pthread_mutex_t)); 
	/**************MUTEX_INITIALISATION**************/
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&ph_id.mt[i], NULL); // initialisation des mutexes :)
		i++;
	}
	/************* LES PHILOSOPHER PAIRE*************/
 	i = 0;
	while (i < data->nbr_philo)
	{
		ph_id.position = (int *)malloc(sizeof(int));  // pliz read again why you use this :)
		*(ph_id.position) = i;
		if (pthread_create(&ph_id.tr[i], NULL, &routine, &ph_id) != 0)//arguments // n'oublier pas de proteger cette fonction :D
			return (write(1, "ERROR : CREAT THREAD :D\n", 24));
		usleep(50);
		i += 2;
	}
	/***************LES PHILOSOPHERS IMPAIRE *************/
	i = 1;
	while (i < data->nbr_philo)
	{
		ph_id.position = (int *)malloc(sizeof(int));  // pliz read again why you use this :)
		*(ph_id.position) = i;
		if (pthread_create(&ph_id.tr[i], NULL, &routine, &ph_id) != 0)//arguments // n'oublier pas de proteger cette fonction :D
			return (write(1, "ERROR : CREAT THREAD :D\n", 24));
		i += 2;
		usleep(50);
	}
	/***************join all philosophers*********************/
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_join(ph_id.tr[i], NULL) != 0)// see arguments // n'oubier pas  la protectionq
			return (write(1, "ERROR : JOIN THREAD :D\n", 24));
		i++;
	}
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&ph_id.mt[i]); // destroy des mutexes :)
		i++;
	}
	return (0);
}