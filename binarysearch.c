#include <stdio.h>

#define SIZE 100
struct {
	int key;
	int data;
} table[SIZE];

int main(){
	int n=0, key, data;
	for(;;){
		putchar('>'); char c = getchar();
		if (c == 'q') break;
		else if(c == '\n' || c == ' ') continue;
		if (c == 'a'){ // add
			putchar('>');putchar('>');scanf("%d %d", &key, &data);
			int low = 0;
			int high = n-1;
			int middle;

			for(;low <= high;){
				middle = (low + high) / 2;
				if(table[middle].key == key)
					{table[middle].data = data;break;}
				else if (table[middle].key < key)
					low = middle + 1;
				else if (table[middle].key > key)
					high = middle - 1;
			}

			const int is_found = (low <= high);
			if(is_found) continue;
			for(int i = n; i > low; --i)
				table[i] = table[i-1];
			table[low].key = key;
			table[low].data = data;
			++n;
		}
		else if (c == 's'){ // search
			putchar('>');putchar('>');scanf("%d", &key);
			int low = 0;
			int high = n-1;
			int middle;

			for(;low <= high;){
				middle = (low + high) / 2;
				if (table[middle].key == key)
					{printf("s>>> %d : %d %d\n", middle, table[middle].key, table[middle].data);break;}
				else if (table[middle].key < key)
					low = middle + 1;
				else if (table[middle].key > key)
					high = middle - 1;
			}
		}
		else if (c == 'd'){ // delete
			putchar('>');putchar('>');scanf("%d", &key);
			int low = 0;
			int high = n-1;
			int middle;

			for(;low <= high;){
				middle = (low + high) / 2;
				if(table[middle].key == key){
					for(int i = middle; i < n-1 ; ++i)
						table[i] = table[i+1];
					--n;
					break;
				} else if (table[middle].key < key)
					low = middle + 1;
				else if (table[middle].key > key)
					high = middle - 1;
			}
		}

		// display array
		for(int i = 0; i < n; ++i) printf("%d : %d %d\n", i, table[i].key, table[i].data);
	}

	// display array
	puts("terminated");
	for(int i = 0; i < n; ++i) printf("%d : %d %d\n", i, table[i].key, table[i].data);
	return 0;
}
