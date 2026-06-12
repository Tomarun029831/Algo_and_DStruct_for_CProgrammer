#include <stdio.h>

#define SIZE 100
struct {
	int key;
	int data;
} table[SIZE];

int main(){
	int key, data, n=0;
	for(;;){
		putchar('>'); int c = getchar();
		if (c == 'q') break;
		else if (c == '\r' || c == '\n' || c == ' ') continue;
		if(c == 'a'){
			putchar('a');putchar('>');putchar('>');
			scanf("%d %d", &key, &data);
			table[n].key = key;
			table[n].data = data;
			++n;
		}
		else if(c == 's'){
			putchar('s');putchar('>');putchar('>');
			scanf("%d", &key);
			for(int i = 0; i < n; ++i)
				if(table[i].key == key)
					printf("s>>> %d : %d %d\n", i, table[i].key, table[i].data);
		}
		else if(c == 'd'){
			putchar('d');putchar('>');putchar('>');
			scanf("%d", &key);
			int i;
			for(i = 0; i < n; ++i)
				if(table[i].key == key){ // delete
					table[i].key = 0;
					table[i].data = 0;
					--n;
				}
			for(;i < n-1; ++i)
				table[i] = table[i+1];
		}

		// display array
		for(int i = 0; i < n; ++i) printf("%d : %d %d\n", i, table[i].key, table[i].data);
	}
	puts("terminated");
	for(int i = 0; i < n; ++i) printf("%d : %d %d\n", i, table[i].key, table[i].data);

	return 0;
}
