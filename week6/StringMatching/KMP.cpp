//ref: http://www-igm.univ-mlv.fr/~lecroq/string/node8.html


#include <stdio.h>
#include <stdlib.h>
void preKmp(char *x, int m, int kmpNext[]) {
	int i, j;

	i = 0;
	j = kmpNext[0] = -1;
	while (i < m) {
		while (j > -1 && x[i] != x[j])
			j = kmpNext[j];
		i++;
		j++;
		if (x[i] == x[j])
			kmpNext[i] = kmpNext[j];
		else
			kmpNext[i] = j;
	}
}


void KMP(char *x, int m, char *y, int n) {
	printf("KMP ");
	int i, j;
	int* kmpNext = (int*)malloc(m*sizeof(int));

	/* Preprocessing */
	preKmp(x, m, kmpNext);

	/* Searching */
	i = j = 0;
	while (j < n) {
		while (i > -1 && x[i] != y[j])
			i = kmpNext[i];
		i++;
		j++;
		if (i >= m) {
			printf("%d\t",(j - i));
			i = kmpNext[i];
		}
	}
	putchar('\n');
}