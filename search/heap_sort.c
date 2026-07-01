#include <stdio.h>
#include <stdlib.h>

void down_heap(int array[], int start, int end){
	int i,j,root=array[start];
	for(i=start,j=2*i; j<=end; i=j,j=2*i){
		if(j<end&&array[j]>array[j+1]) ++j;
		if(root<array[j]) break;
		array[i]=array[j];
	}
	array[i] = root;
}

void heap_sort(int array[], int size){
	for(int i = size/2; i>0; --i) down_heap(array, i, size);
	for(int i = size; i>1; --i){
		int t = array[1];
		array[1] = array[i];
		array[i] = t;
		down_heap(array, 1, i-1);
	}
}

int main() {
	#define SIZE 10
	int array[SIZE+1]={0,9,3,3,1,1,12,4,32,4,-2};
	heap_sort(array, SIZE);
	for(int *p = array;p < array+SIZE+1; ++p)
		printf("%d ", *p);

	return 0;
}
