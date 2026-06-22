#include <stdio.h>

void quick(int array[], int *l, int *r){
	if(l >= r) return;
	int *pivot = r, *il = l, *ir = r;
	for(;;){
		for(;*l<*pivot;++l);
		for(;*pivot<=*r&&il<=r;--r);
		if(l>=r) break;
		int t = *l;
		*l = *r;
		*r = t;
	}
	int t = *pivot;
	*pivot = *l;
	*l = t;
	quick(array,il,l-1);
	quick(array,l+1,ir);
}

int main(){
	#define SIZE 10
	int array[SIZE] = {20,41,19,11,21,9,29,10,93,39};
	quick(array, array, array + (SIZE-1));
	for(int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	return 0;
}
