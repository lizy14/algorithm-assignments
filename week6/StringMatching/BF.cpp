//ref: http://www-igm.univ-mlv.fr/~lecroq/string/node3.html

#include <stdio.h>
void BF(char *x, int m, char *y, int n) {
	printf("BF  ");
	int i, j;

	/* Searching */
	for (j = 0; j <= n - m; ++j) {
		for (i = 0; i < m && x[i] == y[i + j]; ++i);
		if (i >= m)
			printf("%d\t",j);
	}
	putchar('\n');
}
