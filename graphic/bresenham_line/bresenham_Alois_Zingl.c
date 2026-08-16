#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
https://zingl.github.io/Bresenham.pdf

選択したピクセルと描画する線との誤差が最小となるよう貪欲にピクセルを選び続ける。
ある関数に対して陰関数f(x, y) = 0が与えられたする。
このときあるピクセルの座標を(x,y)とすると、そのピクセルの誤差はe = f(x,y)で与えられる。
その線に対してそれをまたいだある側では正の値に、一方は負の値に。

^ y
|--------
|ex |exy|
|P  |ey |
*--------> x 図1

図1のように、現在のピクセルがPそして選択候補となる三つのピクセルの誤差がex, exy, eyであるとして、
if |exy| < |ex| then increase x
if |exy| < |ey| then increase y
この上記の不等式は、|ex|, |exy|, |ey| の中で最も小さいピクセルを選ぶための条件式である。
(納得できないなら三つのケースについて実際に値を設定して動かしてみると分かりやすい。)

次に正の勾配を仮定する。(ここでいう正の勾配とは、たとえばある直線がありその傾きが正であること。)
直線が正の勾配であるということは、ex >= exy >= ey が常に真。このとき、
(実際に傾きが正の直線をexyを通過するように書くと分かりやすい)
if ex + exy > 0 then increase x
if ey + exy < 0 then increase y
この上記の不等式は先ほどの絶対値の条件式の目標と全く同じ動作を実現する。
(ただし、正の勾配が仮定されたとき。また、絶対値の条件式を変形するとたどり着くわけではない全く新しい条件と考えてよい。
実際に三つのケースを試すとわかりやすい。)

また、常に対角位置の誤差exyを現在のピクセルの誤差の代わりに保持することで
計算するべきものがex, eyのみになる。
ex, ey を計算するにはexyから1ピクセルの誤差を引けばよい。

導出を省くが直線の方程式を変形すると、
exy = e+dx-dy
ex = exy + dy
ey = exy - dx
が導ける。
ex+exy = 2*exy + dy > 0
=> 2*exy > -dy ...[1]
ey+exy = 2*exy - dx < 0
=> 2*exy < dx ...[2]

[1], [2]に 2*exy=-dy, 2*exy=dxとなるケースを考慮したものが下記のコードの条件式となる。
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
