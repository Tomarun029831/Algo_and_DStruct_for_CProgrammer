#include <stdio.h>
#include <stdlib.h>

typedef struct _Node{
	int value;
	struct _Node *next;
} Node;

// header -> NULL
// header -> 1 -> NULL // return

// header -> 1 -> 2 -> NULL
// header -> 1 -> 2 -> 3 -> NULL
// header -> 1 -> 2 -> 3 -> 4 -> NULL
Node *merge(Node *header){
	if(header==NULL||header->next==NULL) return header;
	Node *a=header,
	     *b=(header->next==NULL)?header->next:header->next->next;
	for(;b!=NULL;a=a->next, b=(b->next==NULL)?b->next:b->next->next); // aは一つずつbは二つずつ進めることでbが終端に着いたとき
									  // aはちょうど半分の位置を指している。
	Node *p = a->next;a->next = NULL;
	Node *right = merge(header), *left = merge(p);

	Node temp;
	p=&temp;
	for(;right != NULL && left != NULL;){
		if(right->value<=left->value){
			p->next=right;
			p=right;
			right=right->next;
		}else{
			p->next=left;
			p=left;
			left=left->next;
		}
	}
	p->next = (right == NULL) ? left : right;
	return temp.next;
}

int main(){
	#define SIZE 10
	int array[SIZE] = {9,3,4,30,103,90,910,1,93,80};

	Node header = {0, NULL}, *p = &header;
	for(int i = 0; i < SIZE; ++i){
		p->next = malloc(sizeof(Node));
		p = p->next;
		p->value = array[i];
	}
	p->next = NULL;
	header.next = merge(header.next);

	for(p = header.next; p != NULL; p = p->next)
		printf("%d ", p->value);
	printf("\n");

	for(p=header.next; p!=NULL;){
		Node *temp = p;
		p = p->next;
		free(temp);
	}

	return 0;
}
