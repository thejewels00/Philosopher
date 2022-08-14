#include "philo.h"
# include <limits.h>

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
			return(-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
		nbr = nbr * 10 + str[i++] - '0';
	if ((str[i] < 48 || str[i] > 57) && str[i])
		return(-1);
	if (nbr > INT_MAX)
		return (-1);
	return (nbr);
}
