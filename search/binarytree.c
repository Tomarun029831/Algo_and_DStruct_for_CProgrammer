#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int data;
	struct _node *right, *left;
} Node;

Node *init(int key){
	Node *new = malloc(sizeof(Node));
	new->data = key;
	new->right = NULL;
	new->left = NULL;

	return new;
}

Node *search(int key, Node *root){
	for (Node *p = root; p != NULL; p = (p->data < key) ? p->right : p->left)
		if (p->data == key) return p;
	return NULL;
}

Node *insert(int key, Node **root){
	Node *new = malloc(sizeof(Node));
	if(new == NULL) return NULL;
	new->data = key;
	new->right = NULL;
	new->left = NULL;

	Node **p;
	for (p = root; *p != NULL; p = ((*p)->data < key) ? &((*p)->right) : &((*p)->left))
		if ((*p)->data == key) return NULL;
	*p = new;
	return *p;
}

Node *deletemin(Node **node){
	Node **p;
	for(p=node; (*p)->left != NULL; p=&((*p)->left));
	Node *x = *p;
	*p = (*p)->right;
	return x;
}

int delete(int key, Node **root){
	if (*root == NULL) return 0;

	Node **p;
	for (p = root; *p != NULL; p = ((*p)->data < key) ? &((*p)->right) : &((*p)->left))
		if ((*p)->data == key){
			Node *x = *p;
			if ((*p)->right == NULL && (*p)->left == NULL) *p = NULL;
			else if ((*p)->right == NULL) *p = (*p)->left;
			else if ((*p)->left == NULL) *p = (*p)->right;
			else {
				Node *min = deletemin(&((*p)->right));
				min->left = (*p)->left;
				min->right = (*p)->right;
				*p = min;
			}
			free(x);
			return 1;
		}
	return 0;
}

int main(){
	Node *root = NULL;

	insert(5, &root);
	insert(3, &root);
	insert(7, &root);
	insert(2, &root);
	insert(4, &root);

	printf("search 4: %s\n", search(4, root) ? "found" : "none");

	delete(3, &root);
	printf("after deleting 3: %s\n", search(3, root) ? "found" : "none");
	printf("after deleting 4: %s\n", search(4, root) ? "found" : "none");

	free(search(2, root));
	free(search(4, root));
	free(search(7, root));
	free(root);
	return 0;
}
