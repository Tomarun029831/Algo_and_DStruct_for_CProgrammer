#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
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
	const float dx=last->x-first->x;
	const float dy=last->y-first->y;
	const int steps=fmaxf(fabsf(dx),fabsf(dy));
	printf("dx=%f dy=%f steps=%d\n", dx, dy, steps);
	if (steps==0) {FRAMEBUFFER(first->x, first->y)=1; return;}
	const float slope_x=dx/steps;
	const float slope_y=dy/steps;
	printf("slope_x=%f, slope_y=%f\n", slope_x, slope_y);

	/*
	 * y = a * x + b
	 * <->
	 * x = t, y = a * t + b
	 * <->
	 * x = (t - b) / a, y = t
	*/
	for (int t=0; t<=steps; ++t) {
		const int x=roundf(slope_x*t+first->x);
		const int y=roundf(slope_y*t+first->y);
		printf("x=%d, y=%d\n", x, y);
		FRAMEBUFFER(x, y)=1;
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
		drawline_algebraic(&first, &last, framebuffer);
		printf("Octant %d\n", i);
		display(framebuffer);
		memset(framebuffer, 0, sizeof(framebuffer));
	}

	return 0;
}
