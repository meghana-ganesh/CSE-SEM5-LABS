#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
int buf[5],f=-1,r=-1;
sem_t mutex,full,empty;
void *produce(void *arg)
{
	int i;
	for(i=0;i<10;i++)
	{
		sem_wait(&empty); //empty = 4
		sem_wait(&mutex); //mutex = 0
		printf("produced item is %d\n",i);
		buf[(++r)%5]=i;
		sleep(1);
		sem_post(&mutex); //mutex = 1
		sem_post(&full); //full = 1
		printf("full %u\n",full);
		// sleep(1);
	}
}

void *consume(void *arg)
{
	int item,i;
	for(i=0;i<10;i++)
	{
		sem_wait(&full); //full = 0
		printf("full %u\n",full);
		sem_wait(&mutex);
		item=buf[(++f)%5];
		printf("consumed item is %d\n",item);
		sleep(1);
		sem_post(&mutex);
		sem_post(&empty);
	}
}

int main()
{
	pthread_t tid1,tid2;
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,5);
	pthread_create(&tid1,NULL,produce,NULL);
	pthread_create(&tid2,NULL,consume,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}