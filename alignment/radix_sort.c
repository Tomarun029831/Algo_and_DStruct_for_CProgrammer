#include <stdio.h>

typedef struct _node{
	int key;
	int data;
}Node;

#define MASK 0x0f
#define SIZE 10
#define BIT_MAX 15
void radix_sort(short a[], short b[], int size){
	int count[BIT_MAX+1];
	for(int bit = 0; bit < 8 * sizeof(short); bit += 4){
		for(int i = 0; i <= BIT_MAX; ++i) count[i]=0;
		for(int i = 0; i<size; ++i) ++count[(a[i]>>bit)&MASK];
		for(int i = 0; i<BIT_MAX; ++i) count[i+1]+=count[i];
		for(int i = size-1; i>=0; --i) b[--count[(a[i]>>bit)&MASK]] = a[i];
		for(int i = 0; i < size; ++i) a[i] = b[i]; // PERF:
	}
}

int main(){
	short key[SIZE]={91,91,91,78,45,20,92,10,10,10}, buff[SIZE];

	radix_sort(key, buff, SIZE);
	for(int i = 0; i < SIZE; ++i) printf("%4d\n", key[i]);
	return 0;
}
