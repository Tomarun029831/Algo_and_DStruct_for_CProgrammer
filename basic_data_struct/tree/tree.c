#include <stdio.h>

struct _node;
struct _connection;
typedef struct _connection {
	struct _node *node;
	struct _connection *connection;
} Connection;

typedef struct _node {
	int label;
	struct _connection *child;
} Node;

int main(){
	Node root;

	return 0;
}
