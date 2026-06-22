#include <stdio.h>

void quick(int array[], int size){
	int *l = array, *r = array + size - 1, *pivot = r;
	if(l >= r) return;
	for(;;){
		for(;*l<*pivot;++l);
		for(;*pivot<=*r&&array<=r;--r);
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
	int array[SIZE] = {20,41,19,11,21,9,29,10,93,39};
	quick(array, SIZE);
	for(int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	return 0;
}
