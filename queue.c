#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 11
typedef struct{
	int front;
	int rear;
	int array[QUEUE_SIZE];
} Queue;

Queue init(){
	Queue queue = {.front=0, .rear=0, .array={0}}; // もし、arrayの型が`int *`でかつinitないのスタック領域へのポインタなら解放されてダングリングポインタとなる
						      // しかし、今回の場合は、値となるのでダングリングポインタにはならない
	return queue;
}

int is_empty(Queue queue){
	return (queue.rear == queue.front);
}

int is_full(Queue queue){
	return (((queue.rear + 1) % QUEUE_SIZE) == queue.front);
}

Queue enqueue(int value, Queue queue){
	if(is_full(queue)) return queue;
	queue.array[queue.rear] = value;
	queue.rear = (queue.rear + 1) % QUEUE_SIZE;
	return queue;
}

int dequeue(Queue *queue){
	if(is_empty(*queue)) exit(1);
	int value = queue->array[queue->front];
	queue->front = (queue->front + 1) % QUEUE_SIZE;
	return value;
}

int main(){
	int i;
	Queue queue = init();
	// dequeue(&queue);
	
	int values[11] = {-1, 0, 2, 3, 4,
			  10, 3, -3, 11, 12, 13};
	// for(i=0;i<11;++i) queue = enqueue(values[i], queue);
	// for(int j = 0; j < 11; ++j) printf("%d ", dequeue(&queue));

	printf("is_empty -> %d\n", is_empty(queue));
	for(i=0; i < 5; ++i) queue = enqueue(values[i], queue);
	for(int j = 0; j < 2; ++j) printf("%d ", dequeue(&queue));
	printf("is_empty -> %d\n", is_empty(queue));
	for(;i<10;++i) queue=enqueue(values[i], queue);
	for(int j = 2; j < 10; ++j) printf("%d ", dequeue(&queue));
	printf("is_empty -> %d\n", is_empty(queue));

	return 0;
}

