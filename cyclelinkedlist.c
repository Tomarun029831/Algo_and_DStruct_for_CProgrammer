#include <stdio.h>
#include <stdlib.h>

typedef struct _cell{
	struct _cell *next;
	int value;
} Cell;

Cell init(Cell *head){
	Cell cell = {head, 0};
	return cell;
}

void insert(int value, Cell *head){
	Cell *new = malloc(sizeof(Cell)),
	     *curr = head;
	if(new == NULL) return;
	new->value = value;

	for(;curr->next!=head;curr=curr->next);
	new->next=curr->next;
	curr->next = new;
}

void delete(int value, Cell *head){
	Cell *curr = head;
	for(;curr->next!=head&&curr->next->value!=value;curr=curr->next);
	if(curr->next==head) return;
	Cell *target = curr->next;
	curr->next=target->next;
	free(target);
}

int has_contained(int value, Cell *head){
	Cell *curr = head->next;
	for(;curr!=head&&curr->value!=value;curr=curr->next);
	if(curr==head) return 0;
	return 1;
}

void print_list(Cell *head) {
	Cell *curr = head->next;
	while (curr != head) {
		printf("%d -> ", curr->value);
		curr = curr->next;
	}
	printf("(head)\n");
}

int main(){
	Cell head = init(&head);

	puts("--- Insertion Test ---");
	insert(30, &head);
	insert(10, &head);
	insert(20, &head);
	
	printf("Current List: ");
	print_list(&head); 

	puts("\n--- Search Test ---");
	if (has_contained(10, &head)) {
		puts("10 is contained.");
	} else {
		puts("10 is NOT contained.");
	}

	if (has_contained(99, &head)) {
		puts("99 is contained.");
	} else {
		puts("99 is NOT contained.");
	}

	puts("\n--- Deletion Test ---");
	puts("Deleting 10...");
	delete(10, &head);
	printf("Current List: ");
	print_list(&head);

	return 0;
}
