/*
By Zhaoyang, April 2016.
*/

#include "matching.h"

int matching(char* a, char* b, int m, int n);

int main() {
	char a[] = "WHEN in the course of human Events, it becomes necessary for one People to dissolve the Political Bands which have connected them with another, and to assume among the Powers of the Earth, the separate and equal Station to which the Laws of Nature and of Nature¡¯s God entitle them, a decent Respect to the Opinions of Mankind requires that they should declare the causes which impel them to the Separation.";
	char b[] = "the";
	int m = strlen(a);
	int n = strlen(b);
	matching(a, b, m, n);
}

int matching(char* a, char* b, int m, int n) {

	matcher matchers[] = { BF, KMP, BM };
	char* names[] = { "BF ", "KMP", "BM " };

	for (auto i = 0u; i < 3/*MAGIC*/; i++) {

		Timing timer;
		double time = 0;
		int times = 0;

		result r;

		while (1) {
			timer.start();
			r = matchers[i](b, n, a, m);
			timer.end();
			times += 1;
			time += timer.getCPUtime();
			if (time > 10000) {
				time /= times;
				break;
			}
		}

		cout << names[i] << '\t';
		cout << r.size() << '\t';
		for (auto index : r) {
			cout << index << ", ";
		}
		cout << time << " us";
		cout << endl;
	}

	return 0;
}