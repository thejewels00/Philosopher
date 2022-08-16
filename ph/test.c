#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long long	time_in_ms(struct timeval	time)
{
	long long	i;

	return (i = time.tv_sec * 1000 + time.tv_usec * 0.001);
}


int main()
{
	struct timeval	start;
	struct timeval	end;

	

	// int	i = 1;
	gettimeofday(&start, NULL);
	while (1) {

	// if (i == 1)
	// {
	// 	printf("hello it's me 11111 : %d\n", 0);
	// 	i = 0;
	// }
	// else
	// {
	// 	sleep(1);
	// 	gettimeofday(&end, NULL);
	// 	printf("hello it's 1 : %lld\n", time_in_ms(end) - time_in_ms(start));
	// }

	usleep(1000000);
	gettimeofday(&end, NULL);
	printf("hello it's 2 : %lld\n", time_in_ms(end) - time_in_ms(start));

	}

}

