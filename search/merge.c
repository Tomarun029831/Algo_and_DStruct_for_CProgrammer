#include <stdio.h>

#define SIZE 10
// 1 2 3 4 5
// size=5->size/2=2.5=2
#define BUFFER_SIZE SIZE
void merge(int array[], int size){
	int left_size=size/2, right_size=size-left_size;
	int *low=array, *mid=low+left_size, *high=array+size-1;
	if(low>=high) return;

	merge(low, left_size);
	merge(mid, right_size);

	int buff[BUFFER_SIZE];
	for(;low<array+size; ++low)
		buff[low-array] = (low<array+left_size) ? *low : *(high--);

	low = buff, high = buff+size-1;
	for(int *i=array; i<array+size; ++i)
			*i = (*low<=*high) ? *(low++) : *(high--);
}

int main(){
	int array[SIZE] = {10,11,5,6,3,2,12,34,54,45};
	merge(array, SIZE);
	for(int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	return 0;
}
