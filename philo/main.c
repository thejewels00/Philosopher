/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:27:42 by jchennak          #+#    #+#             */
/*   Updated: 2022/08/24 00:40:51 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_args	*time;
	int		i;

	time = (t_args *)malloc(sizeof(t_args));
	if (!time)
		return (0);
	i = input(argv, time, argc);
	if (i == 1)
	{
		if (philosophers(time) != 0)
		{
			return (1);
			free(time);
		}
	}
	else if (i == -1)
	{
		write(2,
			"USAGE : ./philo NB_PHILO TO_DIE TO_EAT TO_SLEEP OPTIONE[NB_EAT]\n",
			65);
		free(time);
		return (1);
	}
	free(time);
	return (0);
}
