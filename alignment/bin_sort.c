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
void bin_sort(Node node[], int size){
	Node bin[KEY_MAXVALUE+1];
	for (int i = 0; i <= KEY_MAXVALUE; ++i) bin[i].key = -1;
	for(int i = 0; i < size; ++i) bin[node[i].key] = node[i];
	for(int i = 0, j = 0; i < KEY_MAXVALUE; ++i)
			if(bin[i].key != -1)
				node[j++] = bin[i];
}

#define SIZE 10
int main(){
	Node nodes[SIZE];
	int keys[SIZE] = {4,3,49,32,2,9,10,11,34,12};
	int datas[SIZE] = {4,3,49,32,2,9,10,11,34,12};
	for(int i = 0; i < SIZE; ++i) nodes[i] = create_node(keys[i],datas[i]);

	bin_sort(nodes, SIZE);
	puts("KEY  DATA");
	for(int i = 0; i < SIZE; ++i)
		printf("%4d %4d\n", nodes[i].key, nodes[i].data);

	return 0;
}
