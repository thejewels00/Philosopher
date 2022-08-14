
void *func(int n)
{
	printf(“\nPhilosopher %d is thinking “,n);
	pthread_mutex_lock(&chopstick[n]);//when philosopher 5 is eating he takes fork 1 and fork 5
	pthread_mutex_lock(&chopstick[(n+1)%5]);
	printf(“\nPhilosopher %d is eating “,n);
	sleep(3);
	pthread_mutex_unlock(&chopstick[n]);
	pthread_mutex_unlock(&chopstick[(n+1)%5]);
	printf(“\nPhilosopher %d Finished eating “,n);
}