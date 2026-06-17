#include <stdio.h>
#include <stdlib.h>

#define MAX_GAKUSEI 2000
#define MAX_KAMOKU 400

struct SEISEKI{
	struct SEISEKI *glink;
	struct SEISEKI *klink;
	short seiseki;
};

struct SEISEKI gakusei[MAX_GAKUSEI];

struct SEISEKI kamoku[MAX_KAMOKU];

void init(){
	for(int i = 0; i < MAX_GAKUSEI; ++i) gakusei[i].glink = gakusei + i;
	for(int i = 0; i < MAX_KAMOKU; ++i) kamoku[i].klink = kamoku + i;
}

void add(int x, int y, short a){
	struct SEISEKI *p = malloc(sizeof(struct SEISEKI));
	if (p == NULL) exit(1);
	p->seiseki=a;

	p->glink=(gakusei+x)->glink;
	(gakusei+x)->glink=p;
	p->klink=(kamoku+y)->klink;
	(kamoku+y)->klink=p;
}

short get_score(int x, int y){
	for (struct SEISEKI *p = gakusei[x].glink; p != gakusei+x; p=p->glink)
		for (struct SEISEKI *q = p->klink;q != p;q=q->klink)
			if (q==kamoku+y) return p->seiseki;
	return -1;
}

void print_kamoku(int y){
	puts("kamoku");
	for (struct SEISEKI *p = kamoku[y].klink;p!=kamoku+y;p=p->klink)
		printf("\t%d\n", p->seiseki);
}

int main(){
	init();

	// テストデータの追加
	// 学生0: 科目0(85点), 科目1(90点)
	add(0, 0, 85);
	add(0, 1, 90);

	// 学生1: 科目0(70点)
	add(1, 0, 70);

	// 学生2: 科目1(95点)
	add(2, 1, 95);

	// 1. 特定の学生の成績検索テスト
	puts("--- get_score Test ---");
	printf("Student 0, Kamoku 1: %d\n", get_score(0, 1)); // 期待値: 90
	printf("Student 1, Kamoku 1: %d\n", get_score(1, 1)); // 期待値: -1 (未履修)

	puts("");

	// 2. 科目ごとの成績一覧表示テスト
	print_kamoku(0); // 期待値: 学生1(70点) -> 学生0(85点) ※逆順に辿るため
	print_kamoku(1); // 期待値: 学生2(95点) -> 学生0(90点)

	return 0;
}
