#include <stdio.h>
#include <stdlib.h>

typedef struct _cell {
	struct _cell *next;
	int value;
} Cell;

Cell init(){
	Cell cell = {NULL, 0};
	return cell;
}

Cell insert(int value, Cell header){
	Cell *new = malloc(sizeof(Cell)),
	     *prev=&header,
	     *curr=header.next;
	new->value=value;
	if(new == NULL) return header;

	for(;curr!=NULL&&curr->value<value;prev=curr,curr=curr->next);
	new->next=prev->next;
	prev->next=new;
	return header;
}

Cell delete(int value, Cell header){
	Cell *prev=&header,
	     *curr=header.next;

	for(;curr!=NULL&&curr->value!=value;prev=curr,curr=curr->next);
	if(curr==NULL) return header; // `value` is not found
	prev->next=curr->next;
	free(curr);
	return header;
}

int has_contained(int value, Cell header){
	Cell *curr=header.next;

	for(;curr!=NULL&&curr->value!=value;curr=curr->next);
	if(curr==NULL) return 0; //false
	return 1;
}

void print_list(Cell *header) {
    Cell *curr = header->next;
    while (curr != NULL) {
        printf("%d -> ", curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main(){
	Cell header = init();

	header = insert(30, header);
	header = insert(10, header);
	header = insert(20, header);
	
	puts("after insertion");
	print_list(&header); // expected result: 10 -> 20 -> 30 -> NULL

	if (has_contained(20, header)) puts("20 is contained in the list");

	header = delete(20, header);
	puts("after deleting 20");
	print_list(&header);
	return 0;
}
