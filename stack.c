#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
typedef struct _stack {
	int sp; // stack pointer
	int array[SIZE];
} STACK;

STACK init(STACK stack);
STACK init(STACK stack){
	stack.sp = 0;
	return stack;
}

STACK push(int value, STACK stack);
STACK push(int value, STACK stack){
	if(stack.sp >= SIZE) exit(1);
	stack.array[stack.sp++] = value;
	return stack;
}

int pop(STACK* stack);
int pop(STACK* stack){
	if(stack->sp <= 0) exit(1);
	int value = stack->array[--stack->sp];
	stack->array[stack->sp] = 0;
	return value;
}

int is_empty(STACK stack);
int is_empty(STACK stack){
	return (stack.sp == 0);
}

// 1 * 2 + 2 -> 1 2 * 2 +
int main(){
	STACK stack;
	stack = init(stack);
	for(;;){
		int c = getchar();
		if (c == '\r' || c == '\n' || c == EOF) {
			if(!is_empty(stack)) printf("%d\n", pop(&stack));
			break;
		}
		else if(c == ' ') continue;

		int a,b;
		switch(c) {
			case '+':
				b = pop(&stack);
				a = pop(&stack);
				stack = push(a + b, stack);
				break;
			case '-':
				b = pop(&stack);
				a = pop(&stack);
				stack = push(a - b, stack);
				break;
			case '*':
				b = pop(&stack);
				a = pop(&stack);
				stack = push(a * b, stack);
				break;
			case '/':
				b = pop(&stack);
				a = pop(&stack);
				stack = push(a / b, stack);
				break;
			default:
				stack = push(c-'0', stack);
		}
	}
	return 0;
}

