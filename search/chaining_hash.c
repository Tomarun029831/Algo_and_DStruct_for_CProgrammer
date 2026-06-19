#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 50
typedef struct _key{
	int header;
} Key;
int compare(Key key1, Key key2){
	if(key1.header == key2.header) return 1;
	return 0;
}

typedef struct _data{
	int detail;
} Data;

typedef struct _cell{
	Key key;
	Data data;
	struct _cell *next;
} Cell;

int hash(Key key){
	return key.header % BUCKET_SIZE;
}

void init(Cell *table[], int size){
	for(int i = 0; i < size; ++i)
		table[i] = NULL;
}

Data *find(Key key, Cell *table[]){
	for(Cell *p = table[hash(key)]; p!=NULL; p=p->next)
		if(compare(p->key, key))
			return &(p->data);
	return NULL;
}

int insert(Key key, Data *data, Cell *table[], int size){
	if(find(key, table) != NULL) return 0;
	Cell *p = malloc(sizeof(Cell));
	p->key = key;
	p->data = *data;
	int h = hash(key);
	p->next = table[h];
	table[h] = p;
	return 1;
}

int delete(Key key, Cell *table[]){
	if(find(key, table) == NULL) return 0;
	int h = hash(key);

	if(compare(table[h]->key, key)){
		Cell *p = table[h];
		table[h] = table[h]->next;
		free(p);
		return 1;
	}

	for(Cell *prev = table[h], *curr = prev->next; curr != NULL; prev=curr, curr=curr->next){
		if(compare(curr->key, key)){
			prev->next=curr->next;
			free(curr);
			return 1;
		}
	}
	return 0;
}

int main() {
    Cell *table[BUCKET_SIZE];
    init(table, BUCKET_SIZE);

    // Prepare test data
    Key k1 = {10};  Data d1 = {100}; // hash(k1) = 10
    Key k2 = {60};  Data d2 = {200}; // hash(k2) = 10 (Collision with k1)
    Key k3 = {10};  Data d3 = {300}; // Duplicate key

    printf("--- Insertion Test ---\n");
    printf("Insert k1: %s\n", insert(k1, &d1, table, BUCKET_SIZE) ? "Success" : "Failed");
    printf("Insert k2: %s (Collision)\n", insert(k2, &d2, table, BUCKET_SIZE) ? "Success" : "Failed");
    printf("Insert k3: %s (Duplicate)\n", insert(k3, &d3, table, BUCKET_SIZE) ? "Success" : "Failed");

    printf("\n--- Search Test ---\n");
    Data *found;
    
    found = find(k1, table);
    if (found != NULL) printf("k1 data: %d\n", found->detail);
    
    found = find(k2, table);
    if (found != NULL) printf("k2 data: %d\n", found->detail);

    printf("\n--- Deletion Test ---\n");
    printf("Delete k2: %s\n", delete(k2, table) ? "Success" : "Failed"); 
    
    found = find(k2, table);
    printf("Search k2 after deletion: %s\n", (found != NULL) ? "Found" : "Not Found");
    
    found = find(k1, table);
    printf("Search k1 (remaining): %s (data: %d)\n", (found != NULL) ? "Found" : "Not Found", found ? found->detail : 0);

    // Clean up remaining memory
    delete(k1, table);

    return 0;
}
