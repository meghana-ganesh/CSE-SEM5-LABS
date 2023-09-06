#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct PositiveNos
{
	int a;
	int b;
}PositiveNos;

void* child_thread(void *param)
{
	PositiveNos *input = (PositiveNos*)param;
	int sum = input->a + input->b;
	return sum;
}
int main(int argc,char *argv[])
{
	pthread_t thread;
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	PositiveNos  input;
	input.a = a;
	input.b = b;
	int sum = 0;
	pthread_create(&thread,0,&child_thread,(void*)&input);
	pthread_join(thread,(void*)&sum);
	printf("the sum is:%d",sum);
}