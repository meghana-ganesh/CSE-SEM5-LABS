#include<stdio.h>
#include<stdlib.h>

typedef struct Queue{
    int *queue;
    int front,rear,capacity;
}Queue;

void enqueue(Queue *pq,int ele){
    if(pq->rear == pq->capacity-1){
        printf("Queue is full\n");
    }
    else{
        if(pq->front == -1)
            pq->front = 0;
        pq->rear = (pq->rear + 1) % pq->capacity;
        pq->queue[pq->rear] = ele;
    }
}

int dequeue(Queue *pq){
    int ele;
    if(pq->front == -1)
        return 0;
    else{
        ele = pq->queue[pq->front];
        pq->front = (pq->front + 1) % pq->capacity;
        return ele;
    }

}

void display(Queue *pq){
    for(int i=pq->front;i<pq->rear+1;i++){
        printf("%d ",pq->queue[i]);
    }
}

int main(){
    Queue *pq,q;
    pq = &q;
    pq->front = pq->rear = -1;
    printf("Enter capacity:\n");
    scanf("%d",&pq->capacity);
    pq->queue = (int*)malloc(pq->capacity*sizeof(int));
    enqueue(pq,2);
    enqueue(pq,4);
    enqueue(pq,6);
    display(pq);
    printf("\n");
    display(pq);
    return 0;
}
