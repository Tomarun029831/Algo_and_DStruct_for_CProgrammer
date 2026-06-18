#include <stdio.h>

#define SIZE 100
struct {
	int key;
	int data;
} table[SIZE];

int address_from(int key){ // mock instead of hash function.
	return key % SIZE;
}

int main(){
	int key, data;
	for(;;){
		putchar('>'); char c = getchar();
		if(c == '\r' || c == '\n' || c == ' ') continue;
		else if (c == 'q') break; // quit
		
		if(c == 'a'){ // add
			putchar('>');putchar('>');scanf("%d %d", &key, &data);
			int i = address_from(key);
			table[i].key = key;
			table[i].data = data;
		} else if (c == 's'){ // search
			putchar('>');putchar('>');scanf("%d", &key);
			int i = address_from(key);
			if (table[i].key == 0) continue;
			printf("%d : %d %d\n", i, table[i].key, table[i].data);
		} else if (c == 'd'){ // delete
			putchar('>');putchar('>');scanf("%d", &key);
			int i = address_from(key);
			table[i].key = 0;
			table[i].data = 0;
		}
	}
	puts("terminated.")

	return 0;
}
