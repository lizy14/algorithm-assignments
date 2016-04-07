
#include <stdio.h>
#include <string.h>
#include "matching.h"
#include "timing.h"

typedef void(*matcher) (char *x, int m, char *y, int n);

int main(){
	char a[] = "the quick brown fox jumps over the lazy dog";
	char b[] = "the";
	int m = strlen(a);
	int n = strlen(b);

	matcher matchers[] = { BF, KMP, BM };
	for (auto f : matchers) {
		f(b, n, a, m);
	}

	return 0;
}