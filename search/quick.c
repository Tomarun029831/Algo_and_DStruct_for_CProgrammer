#include <stdio.h>

void quick(int array[], int size){
	int *pivot = array+size-1, *l = array-1, *r = pivot;
	if(l+1 >= r) return;
	for(;;){
		for(;*(++l)<*pivot;);
		for(;array<=r&&*pivot<=*(--r););
		if(l>=r) break;
		int t = *l;
		*l = *r;
		*r = t;
	}
	int t = *pivot;
	*pivot = *l;
	*l = t;
	quick(array,l-array);
	quick(l+1,(array+size-1)-l);
}

int main(){
	#define SIZE 10
	int array[SIZE] = {2, -1,93,9, 392, 2, 29,3, 91,0};
	quick(array, SIZE);
	for(int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	return 0;
}
