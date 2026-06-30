#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 10
typedef struct _heap{
	int heap[HEAP_SIZE+1];
	int sp;
} Heap;

void up_heap(Heap *heap){
	int i,j, last=heap->heap[heap->sp];
	for(i=heap->sp,j=i/2; j>0&&last<=heap->heap[j]; i=j,j=i/2)
		heap->heap[i]=heap->heap[j];
	heap->heap[i] = last;
}

void insert(int value, Heap *heap){
	if(heap->sp+1>HEAP_SIZE) return;
	heap->heap[++(heap->sp)] = value;
	up_heap(heap);
}

void down_heap(Heap *heap){
	int i,j,root = heap->heap[1];
	for(i=1,j=2*i; i<heap->sp/2; i=j,j=2*i){
		if(j+1<heap->sp&&heap->heap[j]>heap->heap[j+1]) ++j;
		if(root<heap->heap[j]) break;
		heap->heap[i]=heap->heap[j];
	}
	heap->heap[i] = root;
}

int delete_min(Heap *heap){
	if(heap->sp < 1) exit(1);

	int root = heap->heap[1];
	heap->heap[1] = heap->heap[heap->sp--];
	down_heap(heap);

	return root;
}

int main() {
    Heap heap = {{0}, 0};

    int data[] = {5, 3, 8, 1, 9};
    for (int i = 0; i < 5; i++) {
        insert(data[i], &heap);
    }

    printf("Deleted: ");
    while (heap.sp > 0) {
        printf("%d ", delete_min(&heap));
    }
    printf("\n");

    return 0;
}
