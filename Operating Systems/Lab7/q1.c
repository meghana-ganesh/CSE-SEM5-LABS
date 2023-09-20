#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
int buf[10],f=-1,r=-1;
sem_t full,mutex,empty;

void* producer(void *params)
{
	for(int i=0;i<10;i++)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		printf("\nproducer item is:%d",i);
		buf[(r++) % 10] = i;
		sleep(1);
	}
}

void* consumer(void *params)
{

}

int main()
{
	pthread_t tid1,tid2;
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,5);
	pthread_create(&tid1,0,&producer,0);

}
