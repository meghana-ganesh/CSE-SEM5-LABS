#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
void* child_thread( void * param )
{
	int id = (int)param;
	int *arr_fib = (int*)malloc(id*sizeof(int));
	
	for(int i=0;i<id;i++)
	{
        if(i == 0 || i == 1)
            arr_fib[i] = i;
        else
		    arr_fib[i] = arr_fib[i-1] + arr_fib[i-2];
	}
	return arr_fib;
}

int main(int argc,char *argv[])
{
	pthread_t thread;
	int n = atoi(argv[1]);
	int *arr_fib1;
	pthread_create(&thread, 0, &child_thread,(void*)n);
	pthread_join(thread,(void**)&arr_fib1);
	for (int i=0;i<n;i++)
	{
		printf("%d\n",arr_fib1[i]);
	}
}