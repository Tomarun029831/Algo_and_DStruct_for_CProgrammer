#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

難しすぎる
https://zingl.github.io/Bresenham.pdf

*/

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

static void drawline_bresenham(const Point *const first, const Point *const last, _Bool framebuffer[HEIGHT][WIDTH]){
	int x0 = first->x, y0 = first->y, x1 = last->x, y1 = last->y;
	int dx =  abs(x1-x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1-y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx+dy, e2; /* error value e_xy */
	
	for(;;){  /* loop */
		FRAMEBUFFER(x0, y0) = 1;
		if (x0==x1 && y0==y1) break;
		e2 = 2*err;
		if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
	}
}

int main(){
	memset(framebuffer, 0, sizeof(framebuffer)); // init
	#define AMOUNT_OF_DATASET 8
	const Point points[2][AMOUNT_OF_DATASET] = {
		{ {25, 12}, {25, 12}, {25, 12}, {25, 12}, {25, 12}, {25, 12}, {25, 12}, {25, 12} }, // [0]: first (始点: すべて画面中央の {25, 12})
		// [1]: last (終点: Octant 0 〜 7)
		{
			{40, 17}, // Octant 0 ( 0° ~  45° :  dx >=  dy >= 0)
			{30, 22}, // Octant 1 ( 45° ~  90° :  dy >   dx >= 0)
			{20, 22}, // Octant 2 ( 90° ~ 135° :  dy >  -dx >= 0)
			{10, 17}, // Octant 3 (135° ~ 180° : -dx >=  dy >= 0)
			{10,  7}, // Octant 4 (180° ~ 225° : -dx >= -dy >= 0)
			{20,  2}, // Octant 5 (225° ~ 270° : -dy >  -dx >= 0)
			{30,  2}, // Octant 6 (270° ~ 315° : -dy >   dx >= 0)
			{40,  7}  // Octant 7 (315° ~ 360° :  dx >= -dy >= 0)
		}
	};

	for (int i = 0; i < AMOUNT_OF_DATASET; ++i) {
		const Point first=points[0][i], last=points[1][i];
		drawline_bresenham(&first, &last, framebuffer);
		printf("Octant %d\n", i);
		display(framebuffer);
		memset(framebuffer, 0, sizeof(framebuffer));
	}

	return 0;
}
