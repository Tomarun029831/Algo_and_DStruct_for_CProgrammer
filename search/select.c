#include <stdio.h>

void select(int array[], int n){
	for(int i = 0; i < n-1; ++i){
		int low = array[i];
		int index_low = i;
		for(int j = i+1; j < n; ++j)
			if(array[j] < low){
				low = array[j];
				index_low = j;
			}
		array[index_low] = array[i];
		array[i] = low;
	}
}

int main(){
	#define SIZE 10
	int array[SIZE] = {4,2,23,8,0,18,3,1,91,48};
	select(array, SIZE);
	for(int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	return 0;
}
