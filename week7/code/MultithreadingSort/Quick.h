//ref: https://en.wikipedia.org/wiki/Quicksort
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<class T>
vector<T> getVector(istream& s) {
	vector<T> v;
	int n;
	s >> n;
	for (int i = 0; i < n; i++) {
		int _;
		s >> _;
		v.push_back(_);
	}
	return v;
}

template<class T>
ostream& operator<<(ostream& s, vector<T> v) {
	for (int i = 0; i < v.size(); i++)
		s << v[i] << ' ';
	return s << endl;
}




typedef int T;


int partition(vector<T>& A, int lo, int hi) {
	int pivot = A[hi];
	int i = lo;        // place for swapping
		for (int j = lo; j < hi; j++) {
			if (A[j] <= pivot) {
				swap(A[i], A[j]);
				i++;
			}
		}
	swap(A[i] , A[hi]);
	return i;
}




void quick_sort(vector<T>& A, int lo, int hi) {
	if (lo < hi) {
		int p = partition(A, lo, hi);
			for (int i = 0; i < 2; i++) {
				if (i == 0)
					quick_sort(A, lo, p-1);
				else
					quick_sort(A, p + 1, hi);
			}
	}
}

void p_quick_sort(vector<T>& A, int lo, int hi) {
	if (lo < hi) {
		int p = partition(A, lo, hi);
#ifdef OMP
#pragma omp parallel for num_threads(2)
			for (int i = 0; i < 2; i++) {
				if (i == 0)
					p_quick_sort(A, lo, p - 1);
				else
					p_quick_sort(A, p + 1, hi);
			}
#endif
#ifdef CPP11
			thread child(p_quick_sort, ref(A), p + 1, hi);
			quick_sort(p_A, p + 1, hi);
			child.join();
#endif

	}
}


void quick_sort(vector<T>& arr) {
	quick_sort(arr, 0, arr.size()-1);
}


void p_quick_sort(vector<T>& arr) {
	p_quick_sort(arr, 0, arr.size()-1);
}

