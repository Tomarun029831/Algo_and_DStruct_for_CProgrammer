#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 50
#define EMPTY 0
#define DELETED 1
typedef struct _bucket{
	int key;
	int data;
} Bucket;

int hash(int key){
	return key % BUCKET_SIZE;
}

int rehash(int hashed_value){
	return (hashed_value + 1) % BUCKET_SIZE;
}

void init(Bucket bucket[], int size){
	for(int i = 0; i < size; ++i) bucket[i].key = EMPTY;
}

int *find(int key, Bucket bucket[]){
	int h, i;
	for(h = hash(key), i = 0; bucket[h].key != EMPTY; h = rehash(h), ++i) {
		if(i > BUCKET_SIZE) return NULL;
		if(bucket[h].key == key) return &(bucket[h].data);
	}
	return NULL; // Correctly returns NULL if EMPTY is hit
}

int insert(int key, int data, Bucket bucket[]){
	// Prevent duplicates
	if(find(key, bucket) != NULL) return 0; 
	
	int h, i;
	for(h = hash(key), i = 0; bucket[h].key != EMPTY && bucket[h].key != DELETED; h = rehash(h), ++i) {
		if(i > BUCKET_SIZE) return 0; // Table is full
	}
	
	bucket[h].key = key;
	bucket[h].data = data;
	return 1;
}

int delete(int key, Bucket bucket[]){
	int h, i;
	for(h = hash(key), i = 0; bucket[h].key != EMPTY; h = rehash(h), ++i) {
		if(i > BUCKET_SIZE) return 0;
		if(bucket[h].key == key) {
			bucket[h].key = DELETED;
			return 1;
		}
	}
	return 0; // Key wasn't in the table
}

int main() {
    Bucket bucket[BUCKET_SIZE];
    init(bucket, BUCKET_SIZE);

    printf("--- Insertion Test ---\n");
    printf("Insert 10: %s\n", insert(10, 100, bucket) ? "Success" : "Failed");
    printf("Insert 60: %s (Collision)\n", insert(60, 200, bucket) ? "Success" : "Failed"); // hash(60) == 10
    printf("Insert 10: %s (Duplicate)\n", insert(10, 300, bucket) ? "Success" : "Failed");

    printf("\n--- Search Test ---\n");
    int *res;
    res = find(60, bucket);
    printf("Search 60: %s (Data: %d)\n", res ? "Found" : "Not Found", res ? *res : 0);

    printf("\n--- Deletion & Reuse Test ---\n");
    printf("Delete 10: %s\n", delete(10, bucket) ? "Success" : "Failed");

    res = find(60, bucket);
    printf("Search 60 after deleting 10: %s (Data: %d)\n", res ? "Found" : "Not Found", res ? *res : 0);

    printf("Insert 110: %s (Should reuse deleted slot)\n", insert(110, 500, bucket) ? "Success" : "Failed");
    
    res = find(110, bucket);
    printf("Search 110: %s (Data: %d)\n", res ? "Found" : "Not Found", res ? *res : 0);

    return 0;
}
