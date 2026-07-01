#include <stdio.h>

#define ONEBYTE 256
const char *BM(const char *text, const int text_len, const char *pattern, const int pattern_len){
	if(text==NULL || pattern == NULL || *text=='\0' || *pattern=='\0') return NULL;
	int skip[ONEBYTE];
	for(int i = 0; i<ONEBYTE;++i) skip[i]=pattern_len;
	for(int i = 0; i<pattern_len-1; ++i) skip[(unsigned char)*(pattern+i)] = (pattern_len-1-i);
	int i = pattern_len-1;
	for(;i<text_len;){
		int j = pattern_len-1;
		for(;*(text+i) == *(pattern+j);--i,--j) if(j == 0) return (text+i);
		int delta = ((skip[(unsigned char)text[i]] > pattern_len-j) ? (skip[(unsigned char)text[i]])
										:(pattern_len-j)); // 現在比べているpatternとtextのpatternの末尾と
												   // 比べられたtextの文字の次の位置へ移動する
		i += delta;
	}

	return NULL;
}

int main(void){
    const char *text = "ababbfdsbafkjdsababcfksabdfjseab";
    const char *pattern = "abc";
    const char *result = BM(text, 32, pattern, 3);

    if(result == NULL) {
        printf("Not found\n");
        return 0;
    }

    printf("Index: %td\n", result - text);
    printf("Match: %.3s\n", result);
    return 0;
}
