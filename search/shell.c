#include <stdio.h>

// O(n^(1.25)) となる数列はa_(n+1)=3*a_n+1, a_1=1と実験的に分かっているものを使用
// ただし、任意のa_nについてn/9 > a_nとならなければならない
// 極端に離れている要素をソートしてもほとんど得るところがないかららしい。
void shell(int array[], int size){
	int a=1;
	for(;(size/9)>a;a=(3*a)+1);
	for(;a>0;a/=3)
		for(int i=a;i<size;++i)
			for(int j=i;j>=a&&array[j-a]>array[j];j-=a){
				int t=array[j-a];
				array[j-a]=array[j];
				array[j]=t;
			}
}

int main(){
	#define SIZE 10
	int array[SIZE] = {201,21,40192,84,19,5,129,192,4,10};
	shell(array, SIZE);
	for(int i = 0; i < SIZE; ++i)
		printf("%d ", array[i]);

	return 0;
}
