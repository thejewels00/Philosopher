#include "philo.h"
#include <stdio.h>

// int check_input(t_args inp)
// {
// 	if((inp->life_cercle * inp->nbr_philo * inp->time_to_die) == 0)
// 		return (-1);
	
// }


int	input(char **av, t_args *inp, int argc)
{
	if (argc != 5 && argc != 6)
		return (-1);
	inp->nbr_philo = ft_atoi(av[1]);
	inp->time_to_die = ft_atoi(av[2]);
	inp->time_to_eat = ft_atoi(av[3]);
	inp->time_to_sleep = ft_atoi(av[4]);
	inp->life_cercle = 1;
	if (av[5])
		inp->life_cercle = ft_atoi(av[5]);
	if (inp->life_cercle == -1 || inp->nbr_philo == -1 || inp->time_to_die == -1
		|| inp->time_to_eat == -1 || inp->time_to_sleep == -1)
		return (-1);
	if((inp->life_cercle * inp->nbr_philo * inp->time_to_die) == 0)
		return (0);
	return (1);
}



int main(int argc, char **argv)
{
	t_args	time;
	int		i;

	i = input(argv, &time, argc);
	if(i == 1)
	{
		//printf("hello word");
		if (philosophers(&time)!= 0)
			return (1);
	}
	else if (i == -1)
	{
		write(2,
		"USAGE : ./philo NB_OF_PHILO TO_DIE TO_EAT TO_SLEEP OPTIONELLE[NB_FOR_EAT]\n", 75);
		return (1);
	}
	return (0);
}


