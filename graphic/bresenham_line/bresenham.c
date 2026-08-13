#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

の日本語版,「整数演算の場合」のセクションにおいて、
	陰関数	f(x,y) = Ax + By + C = 0 (ただし、A,B,Cは定数)に対して
	差分	D = f(x0+1),y0+1/2) - f(x0,y0) = f(x0+1),y0+1/2)
	さらに二点目は、
		f(x0+2,y0+1/2) - f(x0+1,y0+1/2) = A
		f(x0+2,y0+3/2) - f(x0+1,y0+1/2) = A + B
	"この差が正なら(x0+2,y0+1)を選び、そうでないなら(x0+2,y0)を選ぶ。"
	と書かれている。これらはすなわち、
		D_0 = f(x_0 + 1),y_0 + 1/2) - f(x_0,y_0) = f(x_0 + 1),y_0 + 1/2) = P_0
		D_k = f(x_k + 1,y_k + 1/2) - f(x_(k-1)+1,y_(k-1)+1/2) (k >= 1)
	と定義し,
	ここで P_k = f(x_k + 1,y_k + 1/2) として
		D_k = P_k - P_(k-1)
	に対して
		sgn(D_k) = sgn(P_k)
	と言っていることと何ら変わりない。しかしこれは間違えである。
	実際は、差の総和の符号で判定するので
		sigma(k=0 to n) {D_k} = P_n ... [1]
	を示せばよい。これは数学的帰納法で証明可能である。(略)
	Bresenham's algorithmの価値は整数演算のみで構成されることにある。
	整数演算のみで構成するためには、
	[1]の両辺を二倍しても成り立ちさらに符号が変化しないことを利用する。

両辺を二倍しても成り立つので
		sigma(k=0 to n) {2 * D_k} = 2 * P_n ... [1]
	ここで2 * D_k, 2 * P_nが共に整数となることを示せばよい。
	直線の方程式 (y - y_0) / (y_1 - y_0) = (x - x_0) / (x_1 - x_0) を変形すると
	f(x,y) = x * (y_1 - y_0) - y * (x_1 - x_0) + y0 d (x_1 - x_0) - x_0 * (y_1 - y_0) = 0 ... [2]
	と変形できる。変数x, y, x_0, x_1, y_0, y_1が整数であればこの関数f(x,y)は整数である。また、
	f(x_0, y_0) = A * x_0 + B * y_0 + C = 0 => C = - (A * x_0 + B * y_0) 
	また[2]よりA = y_1 - y_0, B = x_0 - x_1 と置けば定数A,B,Cは整数である。

	P_k = f(x_k + 1, y_k + 1/2) = A(x_k + 1) + B(y_k + 1/2) + C
		= A * x_k + B * y_k + A + B/2 + C
	=> 2 * P_k = 2A * x_k + 2B * y_k + 2A + B + 2C よって 2 * P_k (ただし、整数k>=0)は整数。

	D_0 = P_0 => 2 * D_0 = 2 * P_0 より 2 * D_0は整数
	D_k = P_k - P_(k-1) => 2 * D_k = 2 * P_k - 2 * P_(k-1) より2 * D_k (整数k>=1)は整数
よって、Bresenham's algorithmを整数演算のみで構成することができた。

次にD_kの具体的な初期値とそれ以降の値について考える。
	[1] 初期値 2 * D_0 の計算:
	始点 (x_0, y_0) では f(x_0, y_0) = A * x_0 + B * y_0 + C = 0 であるため、
	C = - (A * x_0 + B * y_0)

	2 * D_0 = 2 * P_0 = 2 * f(x_0 + 1, y_0 + 1/2)
	        = 2 * [A(x_0 + 1) + B(y_0 + 1/2) + C]
	        = 2A * x_0 + 2A + 2B * y_0 + B + 2C
	
	ここに 2C = -2A * x_0 - 2B * y_0 を代入すると、
	2 * D_0 = 2A + B

	ここで A = y_1 - y_0 = dy, B = x_0 - x_1 = -dx と置けば、
	2 * D_0 = 2 * dy - dx  ... (完全な整数初期値)


	[2] k >= 1 における増分 2 * D_k の場合分け:
	ステップ k における判定値 2 * P_k と前ステップ 2 * P_(k-1) の差分を考える。
	x は毎ステップ必ず 1 増加する (x_k = x_(k-1) + 1)。

	2 * D_k = 2 * P_k - 2 * P_(k-1)
	        = 2 * [A * x_k + B * y_k + A + B/2 + C] - 2 * [A * x_(k-1) + B * y_(k-1) + A + B/2 + C]
	        = 2A(x_k - x_(k-1)) + 2B(y_k - y_(k-1))
	        = 2A + 2B(y_k - y_(k-1))

	ここで直前の判定 2 * P_(k-1) の符号による y_k の選択で分岐する：

	(i) 2 * P_(k-1) < 0 の場合 (y を更新しない: y_k = y_(k-1)):
	    y_k - y_(k-1) = 0 より、
	    2 * D_k = 2A = 2 * dy

	(ii) 2 * P_(k-1) >= 0 の場合 (y を更新する: y_k = y_(k-1) + 1):
	    y_k - y_(k-1) = 1 より、
	    2 * D_k = 2A + 2B = 2 * dy - 2 * dx


	[3] 結論 (状態遷移の漸化式):
	変数 F_k = sigma(i=0 to k) {2 * D_i} と定義すると、ループ内は以下の単純加算で閉じられる。

	初期状態:
	    F_0 = 2 * dy - dx

	状態更新 (k >= 1):
	    F_k = F_(k-1) + (2 * dy)              (if F_(k-1) < 0)
	    F_k = F_(k-1) + (2 * dy - 2 * dx)      (if F_(k-1) >= 0)
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
