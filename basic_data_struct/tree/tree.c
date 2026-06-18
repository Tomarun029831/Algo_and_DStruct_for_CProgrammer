#include <stdio.h>
#include <stdlib.h>

struct _node;
struct _connection;
typedef struct _connection {
	struct _node *node;
	struct _connection *next;
} Connection;

typedef struct _node {
	int label;
	struct _connection *child;
} Node;

Node *init(int label){
	Node *root = (Node *)malloc(sizeof(Node));
	root->label=label;
	root->child=NULL;
	return root;
}

void insert(int label, Node *parent){
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->label = label;
	new_node->child = NULL;
	Connection *new_connection = (Connection *)malloc(sizeof(Connection));
	new_connection->node = new_node;
	new_connection->next = NULL;

	Connection *cnct;
	if(parent->child == NULL) {parent->child = new_connection; return;}
	for(cnct = parent->child; cnct->next != NULL; cnct=cnct->next);
	cnct->next = new_connection;
}

Node *search(int label, Node *node){
	if(node == NULL || node->label == label) return node;
	for(Connection *cnct = node->child; cnct != NULL; cnct=cnct->next){
		Node *node=search(label, cnct->node);
		if(node == NULL) continue;
		return node;
	}
	return NULL;
}

void free_tree(Node *node){
	if(node == NULL) return;
	else if(node->child == NULL) {free(node); return;}

	for(Connection *cnct=node->child; cnct!=NULL;){
		free_tree(cnct->node);
		Connection *next=cnct->next;
		free(cnct);
		cnct=next;
	}
	free(node);
}

void delete(int label, Node *node){
	if(node==NULL||node->child==NULL) return;

	Connection *prev, *curr;
	for(prev=NULL, curr=node->child; curr!=NULL; prev=curr, curr=curr->next)
		if(curr->node->label == label){
			if(prev==NULL) {node->child=curr->next;}
			else {prev->next = curr->next;}
			free_tree(curr->node);
			free(curr);
			return;
		}
}

void print_tree(Node *node, int depth) {
	if (node == NULL) return;
	for (int i = 0; i < depth; i++) printf("  ");
	printf("- [%d]\n", node->label);
	for (Connection *cnct = node->child; cnct != NULL; cnct = cnct->next) {
		print_tree(cnct->node, depth + 1);
	}
}

int main() {
	// 1. Create root node (Root directory)
	Node *root = init(1);
	printf("--- Initial Tree Structure ---\n");
	print_tree(root, 0);

	// 2. Build Level 1 (e.g., /bin, /home, /var)
	insert(10, root); // First child
	insert(20, root); // Second child
	insert(30, root); // Third child

	// 3. Build Level 2 under node 10 (e.g., files under /bin)
	Node *node10 = search(10, root);
	if (node10 != NULL) {
		insert(11, node10);
		insert(12, node10);
	}

	// 4. Build Level 2 and Level 3 under node 20 (e.g., /home/user/documents)
	Node *node20 = search(20, root);
	if (node20 != NULL) {
		insert(21, node20);
		insert(22, node20);
		
		// Move deeper into Level 3 under node 21
		Node *node21 = search(21, root);
		if (node21 != NULL) {
			insert(211, node21);
			insert(212, node21);
		}
	}

	// 5. Build Level 2 under node 30
	Node *node30 = search(30, root);
	if (node30 != NULL) {
		insert(31, node30);
	}

	printf("\n--- Multi-way Tree Structure After Heavy Insertion ---\n");
	print_tree(root, 0);

	// 6. Test search function for a deep leaf node
	int target = 212;
	Node *found = search(target, root);
	if (found != NULL) {
		printf("\n[Search Result]: Deep node [%d] was found.\n", found->label);
	} else {
		printf("\n[Search Result]: Deep node [%d] was not found.\n", target);
	}

	// 7. Test delete function (Delete node 20 from directly under root)
	// This will remove node 20 and ALL its descendants (21, 22, 211, 212) safely.
	printf("\n[Delete Executed]: Deleting node 20 from directly under root.\n");
	delete(20, root);

	printf("\n--- Tree Structure After Deletion ---\n");
	print_tree(root, 0);

	// 8. Free all remaining memory
	free_tree(root);
	printf("\nAll remaining memory has been successfully freed.\n");

	return 0;
}
