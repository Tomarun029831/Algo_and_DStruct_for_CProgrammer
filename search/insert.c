#include <stdio.h>

void insert(int array[], int n){
	for(int i = 1; i < n; ++i)
		for(int j = i; j > 0; --j)
			if(array[j-1]>array[j]){
				int t = array[j-1];
				array[j-1] = array[j];
				array[j] = t;
			}
}

int main(){
	#define SIZE 10
	int array[SIZE]={20,120,12,430,493,493,3,943,-1,-12};
	insert(array, SIZE);
	for(int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	return 0;
}
