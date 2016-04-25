//ref: http://www-igm.univ-mlv.fr/~lecroq/string/node3.html

#include "matching.h"
#pragma optimize( "", off )


result BF(char *x, int m, char *y, int n) {
	result r;
	int i, j;
	/* Searching */
    for (j = 0; j <= n - m; ++j) {
       for (i = 0; i < m; ++i){
           if(x[i] != y[i + j])
               break;
       }
       if (i >= m)
          r.push_back(j);
    }
	return r;
}
#pragma optimize( "", on)

