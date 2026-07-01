#include <stdio.h>

const char *brute_force_search(const char *text, const char *pattern){
	if(text==NULL || pattern==NULL || *text == '\0' || *pattern == '\0') return NULL;
	for(const char *t=text;;++t)
		for(const char *c=t, *p=pattern;;++c,++p)
			if(*p=='\0') return t;
			else if(*c=='\0') return NULL;
			else if(*c!=*p) break;
}

int main(){
	const char *text = "ababbfdsbafkjdsababcfksabdfjseab";
	const char *pattern = "abc";
	const char *result = brute_force_search(text, pattern);
	if(result == NULL) return 0;
	printf("%d\n", result-text);
	for(int i = 0; i < 3; ++i)
		printf("%c", *(result + i));

	return 0;
}
