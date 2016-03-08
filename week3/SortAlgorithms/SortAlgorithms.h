/*
具有 4 种排序方法的 vector 类

Zhaoyang, March 2016
*/

#include "RandomInteger.h"
#include "QuickSort.h"
#include <vector>

class Vector : public vector<unsigned>{
public:
	void randomize(int size){
		RandomInteger r(LENGTH);
		resize(0);
		for(int i=0; i<size; i++){
			push_back(r.get());
		}
	}
	int lg(unsigned x){
		int r=0;
		while(x>>=1){
			r++;
		}
		return r;
	}
	void radixSort(){
		//ref: zh.wikipedia.org
		int n = size();
		auto& data = *this;
		int *tmp = new int[n];

		const int BASE = 32; /*hard coded for 32-bit integers*/
		int d = 7; /*hard coded for 32-bit integers*/

		int *count = new int[BASE]; //counter
		int i, j, k;
		int radix = 1;
		for(i = 1; i <= d; i++){
			for(j = 0; j < BASE; j++)
				count[j] = 0;
			for(j = 0; j < n; j++){
				k = (data[j] / radix) % BASE;
				count[k]++;
			}
			for(j = 1; j < BASE; j++)
				count[j] = count[j - 1] + count[j];
			for(j = n - 1; j >= 0; j--){
				k = (data[j] / radix) % BASE;
				tmp[count[k] - 1] = data[j];
				count[k]--;
			}
			for(j = 0; j < n; j++)
				data[j] = tmp[j];
			radix = radix * BASE;
		}
		delete []tmp;
		delete []count;
	}

	
	void insertionSort() {
		auto& arr = *this;
		auto len = size();

		//reference: zh.wikipedia.org
	    int i, j, temp;
		for (i = 1; i < len; i++) {
			temp = arr[i];
			for (j=i-1; j>=0 && arr[j]>temp; j--)
				arr[j+1] = arr[j];
			arr[j+1] = temp;
		}
	}
	void quickSort(){
		quickSort_<unsigned>(*this);
	}
#include "MergeSort.h"
};

ostream& operator<<(ostream& os, Vector& v){
	for(auto& i : v){
		os << i << endl;
	}
	return os << endl;
}

