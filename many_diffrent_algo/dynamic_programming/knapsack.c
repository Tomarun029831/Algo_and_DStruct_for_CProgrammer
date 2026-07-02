#include <stdio.h>
#include <stdlib.h>

#define AMOUNT_ITEM 5
const int size[AMOUNT_ITEM] = {2,3,5,7,9};
const int value[AMOUNT_ITEM] = {2,4,7,11,14};
int main(int argc, char **argv){
	// init
	if(argc<2) return 1;
	const int knapsack_size=atoi(argv[1]);
	int *const total = (int *const)calloc(knapsack_size+1,sizeof(int));
	if(total==NULL) return 1;
	int *const choice = (int *const)calloc(knapsack_size+1,sizeof(int));
	if(choice==NULL) {free(total); return 1;}
	for(int i = 0; i < knapsack_size+1; ++i){total[i] = 0; choice[i] = -1;}

	// packing items
	for(int i = 0; i < AMOUNT_ITEM; ++i){
		for(int j = size[i]; j < knapsack_size+1; ++j){
			const int new_total = total[j-size[i]] + value[i];
			if(total[j] > new_total) continue;
			total[j] = new_total; choice[j] = i;
		}

		// print status of each array
		printf("size  : "); for(int k = 0; k<knapsack_size+1; ++k) printf("%3d ", k); puts("");
		printf("total : "); for(int k = 0; k<knapsack_size+1; ++k) printf("%3d ", total[k]); puts("");
		printf("choice: "); for(int k = 0; k<knapsack_size+1; ++k) printf("%3d ", choice[k]); puts("\n");
	}

	// show items to maxmize result
	printf("items : "); for(int i = knapsack_size; choice[i] != -1; i -= size[choice[i]]) printf("%3d ", choice[i]);

	// clean-up
	free(total); free(choice);
	return 0;
}
