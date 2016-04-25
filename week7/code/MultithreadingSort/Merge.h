//ref: CLRS Section 27.3
//ref: stackoverflow.com/questions/25750066/c-11-multithread-merge-sort

#include <omp.h>

#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <cstdlib>
#include <algorithm>
using namespace std;

int binary_search(int x, vector<int>& T, int p, int r) {
	int low = p;
	int high = max(p, r + 1);
	while (low < high) {
		int mid = (low + high) / 2;
		if (x <= T[mid]) {
			high = mid;
		}
		else {
			low = mid + 1;
		}
	}
	return high;
}



void merge(vector<int>& T, int p1, int r1, int p2, int r2, vector<int>& A, int p3) {
	int n1 = r1 - p1 + 1;
	int n2 = r2 - p2 + 1;
	if (n1 < n2) {
		swap(p1, p2);
		swap(r1, r2);
		swap(n1, n2);
	}
	if (n1 == 0)
		return;
	else {
		int q1 = (p1 + r1) / 2;
		int q2 = binary_search(T[q1], T, p2, r2);
		int q3 = p3 + (q1 - p1) + (q2 - p2);
		A[q3] = T[q1];

		for (int i = 0; i < 2; i++) {
			if (i == 0)
				merge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
			else
				merge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
		}
	}
}

void merge_sort(vector<int>& A, int p, int r, vector<int>& B, int s) {
	int n = r - p + 1;
	if (n == 1) {
		B[s] = A[p];
	}
	else {
		vector<int> T(n + 1);
		int q = (p + r) / 2;
		int q_ = q - p + 1;

		for (int i = 0;i < 2; i++) {
			if (i == 0)
				merge_sort(A, q + 1, r, T, q_ + 1);
			else
				merge_sort(A, p, q, T, 1);
		}

		merge(T, 1, q_, q_ + 1, n, B, s);
	}
}


void p_merge_sort_naive(vector<int>& A, int p, int r, vector<int>& B, int s) {
	int n = r - p + 1;
	if (n == 1) {
		B[s] = A[p];
	}
	else {
		vector<int> T(n + 1);
		int q = (p + r) / 2;
		int q_ = q - p + 1;
#pragma omp parallel for num_threads(2)
		for (int i = 0;i < 2; i++) {
			if (i == 0)
				merge_sort(A, q + 1, r, T, q_ + 1);
			else
				merge_sort(A, p, q, T, 1);
		}

		merge(T, 1, q_, q_ + 1, n, B, s);
	}
}





void p_merge(vector<int>& T, int p1, int r1, int p2, int r2, vector<int>& A, int p3) {
	int n1 = r1 - p1 + 1;
	int n2 = r2 - p2 + 1;
	if (n1 < n2) {
		swap(p1, p2);
		swap(r1, r2);
		swap(n1, n2);
	}
	if (n1 == 0)
		return;
	else {
		int q1 = (p1 + r1) / 2;
		int q2 = binary_search(T[q1], T, p2, r2);
		int q3 = p3 + (q1 - p1) + (q2 - p2);
		A[q3] = T[q1];
#ifdef OMP
#pragma omp parallel for num_threads(2)
		for (int i = 0; i < 2; i++) {
			if (i == 0)
				p_merge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
			else
				p_merge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
		}
#endif
#ifdef CPP11
		thread child(p_merge, ref(T), q1 + 1, r1, q2, r2, ref(A), q3 + 1);
		p_merge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
		child.join();
#endif
	}
}

void p_merge_sort(vector<int>& A, int p, int r, vector<int>& B, int s) {
	int n = r - p + 1;
	if (n == 1) {
		B[s] = A[p];
	}
	else {
		vector<int> T(n + 1);
		int q = (p + r) / 2;
		int q_ = q - p + 1;
#ifdef OMP
#pragma omp parallel for num_threads(2)
		for (int i = 0;i < 2; i++) {
			if (i == 0)
				p_merge_sort(A, q + 1, r, T, q_ + 1);
			else
				p_merge_sort(A, p, q, T, 1);
		}
#endif
#ifdef CPP11
		thread child(p_merge_sort, ref(A), q + 1, r, ref(T), q_ + 1);
		p_merge_sort(A, p, q, T, 1);
		child.join();
#endif
		p_merge(T, 1, q_, q_ + 1, n, B, s);
	}
}

