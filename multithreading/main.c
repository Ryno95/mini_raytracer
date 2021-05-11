#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *bigcount(void *arg)
{
	for(int i = 0; i < 10000; i++)
	{
		pthread_mutex_lock(&lock);
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

void *your_turn(void *arg)
{
	while(1)
	{
		sleep(1);
		printf("Your turn! \n");
	}
}

int main(void)
{
	pthread_t tid;
	pthread_mutex_lock(&lock);

	pthread_create(&tid, NULL, bigcount, NULL);
	bigcount(NULL);
	pthread_join(tid, NULL);
	printf("counter: %d\n", counter);
	// your_turn(NULL);
	return (0);
}