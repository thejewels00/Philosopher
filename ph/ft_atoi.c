/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:04:38 by jchennak          #+#    #+#             */
/*   Updated: 2022/08/21 15:50:52 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	input(char **av, t_args *inp, int argc)
{
	if (argc != 5 && argc != 6)
		return (-1);
	inp->nbr_philo = ft_atoi(av[1]);
	inp->time_to_die = ft_atoi(av[2]);
	inp->time_to_eat = ft_atoi(av[3]);
	inp->time_to_sleep = ft_atoi(av[4]);
	inp->life_cercle = -2;
	if (av[5])
		inp->life_cercle = ft_atoi(av[5]);
	if (inp->life_cercle == -1 || inp->nbr_philo == -1 || inp->time_to_die == -1
		|| inp->time_to_eat == -1 || inp->time_to_sleep == -1)
		return (-1);
	if ((inp->life_cercle * inp->nbr_philo * inp->time_to_die) == 0)
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while (str [i] == ' ' || (str[i] >= '\b' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
		nbr = nbr * 10 + str[i++] - '0';
	if ((str[i] < 48 || str[i] > 57) && str[i])
		return (-1);
	if (nbr > INT_MAX)
		return (-1);
	return (nbr);
}
