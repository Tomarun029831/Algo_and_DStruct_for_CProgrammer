#include <stdio.h>

/*
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
*/

// without `recursive call`
void quick(int array[], int size){
	#define STACK_SIZE 30
	int *high[STACK_SIZE], *low[STACK_SIZE], sp=1;
	low[0] = array-1, high[0] = array+size-1;

	for(;sp>0;){
		int *pivot = high[--sp], *l = low[sp], *r = pivot;
		if(l+1 >= r) continue;
		for(;;){
			for(;*(++l)<*pivot;);
			for(;array<=--r&&*pivot<=*r;);
			if(l>=r) break;
			int t = *l; *l = *r; *r = t;
		}
		int t = *pivot; *pivot = *l; *l = t;

		low[sp] = low[sp];
		high[sp++] = l-1;
		low[sp] = l+1;
		high[sp++] = high[sp-1];
	}
}

int main(){
	#define SIZE 10
	int array[SIZE] = {8,74,3,4,5,2,1,0,6,11};
	quick(array, SIZE);
	for(int i = 0;i<SIZE;++i)
		printf("%d ", array[i]);

	return 0;
}
