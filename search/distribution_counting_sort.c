#include <stdio.h>

typedef struct _node{
	int key;
	int data;
}Node;

Node create_node(int key, int data){
	Node node = {key, data};
	return node;
}

#define KEY_MAXVALUE 100
void dist_cnt_sort(Node node[], Node out[],int size){
	int count[KEY_MAXVALUE+1];
	for(int i = 0; i<=KEY_MAXVALUE; ++i) count[i]=0;
	for(int i = 0; i < size; ++i) ++count[node[i].key];
	for(int i = 0; i < KEY_MAXVALUE; ++i) count[i+1]+=count[i];
	for(int i = size-1; i >= 0; --i)
		out[--count[node[i].key]] = node[i];
}

#define SIZE 10
int main(){
	Node nodes[SIZE], out[SIZE];
	int keys[SIZE] = {3,3,3,32,2,9,10,11,34,12};
	int datas[SIZE] = {4,3,1,32,2,9,10,11,34,12};
	for(int i = 0; i < SIZE; ++i) nodes[i] = create_node(keys[i],datas[i]);

	dist_cnt_sort(nodes, out, SIZE);
	puts("KEY  DATA");
	for(int i = 0; i < SIZE; ++i)
		printf("%4d %4d\n", out[i].key, out[i].data);

	return 0;
}
