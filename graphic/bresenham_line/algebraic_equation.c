#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct _point{ int x, y; } Point;
#define HEIGHT 25
#define WIDTH 50
/*
* *-----------------------> x
* | .(x1, y1)
* |
* |
* |     .(x2, y2)
* |
* v
*
* y
*/
static _Bool framebuffer[HEIGHT][WIDTH];
#define FRAMEBUFFER(x, y) framebuffer[y][x]

static void display(const _Bool framebuffer[HEIGHT][WIDTH]){
	for (size_t h=0; h<HEIGHT; ++h){
		for (size_t w=0; w<WIDTH; ++w)
			printf("%c", framebuffer[h][w] ? '#' : '.');
		putchar('\n');
	}
	putchar('\n');
}

static void drawline_algebraic(const Point *const first, const Point *const last, _Bool framebuffer[HEIGHT][WIDTH]){
	const float dx = last->x - first->x;
	const float dy = last->y - first->y;
	const float slope = dy/dx;

	for (int x = first->x; x < last->x + 1; ++x) {
		const int y = roundf(slope * (x - first->x) + first->y);
		FRAMEBUFFER(x, y) = 1;
	}
}

int main(){
	memset(framebuffer, 0, sizeof(framebuffer)); // init
	const Point first={0, 0}, last={10, 1};

	drawline_algebraic(&first, &last, framebuffer);
	display(framebuffer);
	memset(framebuffer, 0, sizeof(framebuffer));

	return 0;
}
