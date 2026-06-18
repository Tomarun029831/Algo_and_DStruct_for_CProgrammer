#include <stdio.h>
#include <stdlib.h>

typedef struct _cell{
	struct _cell *prev;
	struct _cell * next;
	int value;
} Cell;

void init(Cell *head){
	head->prev = head;
	head->next = head;
}

void insert(int value, Cell *head){
	Cell *new = (Cell *)malloc(sizeof(Cell)),
	     *curr = head->next;
	if(new == NULL) return;
	new->value = value;

	for(;curr!=head&&curr->value < value; curr=curr->next);
	new->next = curr;
	new->prev = curr->prev;
	curr->prev->next=new;
	curr->prev=new;
}

void delete(int value, Cell *head){
	Cell *curr=head->next;
	for(;curr!=head&&curr->value!=value;curr=curr->next);
	if(curr == head) return; // dont delete the cell at a head and value is not found
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr);
}

void print_forward(Cell *head) {
	Cell *curr = head->next;
	printf("Forward: ");
	while (curr != head) {
		printf("%d -> ", curr->value);
		curr = curr->next;
	}
	printf("(head)\n");
}

void print_backward(Cell *head) {
	Cell *curr = head->prev;
	printf("Backward: ");
	while (curr != head) {
		printf("%d -> ", curr->value);
		curr = curr->prev;
	}
	printf("(head)\n");
}

int main(){
	Cell head;
	init(&head);

	puts("--- Insertion Test ---");
	insert(30, &head);
	insert(10, &head);
	insert(20, &head);
	insert(5, &head);

	print_forward(&head);  // 5 -> 10 -> 20 -> 30 -> (head)
	print_backward(&head); // 30 -> 20 -> 10 -> 5 -> (head)

	puts("\n--- Deletion Test ---");
	puts("Deleting 20...");
	delete(20, &head);
	
	print_forward(&head);  // 5 -> 10 -> 30 -> (head)
	print_backward(&head); // 30 -> 10 -> 5 -> (head)

	return 0;
}
