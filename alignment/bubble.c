#include <stdio.h>

void select(int array[], int n){
	for(int i = 0; i < n-1; ++i)
		for(int j = n-1; j>i; --j)
			if(array[j-1] > array[j]){
				int t = array[j];
				array[j] = array[j-1];
				array[j-1] = t;
			}
}

// 0 1 2 3 4 5 6 7 8 9

int main(){
	#define SIZE 10
	int array[SIZE]={4903,430,930,30,49,4903,043,9,3404,903};
	select(array, SIZE);
	for(int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	return 0;
}
