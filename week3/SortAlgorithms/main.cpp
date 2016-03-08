/*
Algorithms Assignment #3,
By Zhaoyang, March 2016
*/

#include "RandomInteger.h"
#include "timing.h"

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

#define LENGTH (15) // 15, 30, 32

#define MAX ((((unsigned long long)1)<<(LENGTH))-1)

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
		/*
		  0 -> 0
		  1 -> 0
		  2 -> 1
		  3 -> 1
		  4 -> 2
		255 -> 7
		256 -> 8
		257 -> 8
		*/
		int r=0;
		while(x>>=1){
			r++;
		}
		return r;
	}
	void radixSort(){
		int r = lg(size());
		int b = LENGTH;

	}
	void countSort(){
		vector<unsigned int> v(MAX+1, 0); //counter
		for(auto& i : *this){
			v[i]++;
		}
		for(int i=1; i<=MAX; i++){
			v[i] += v[i-1];
		}
		Vector result;
		result.resize(size());

		for(int i=size()-1; i>=0; i--){
			result[v[operator[](i)]-1] = operator[](i);
			v[operator[](i)]--;
		}
		*this = result;
	}
};

ostream& operator<<(ostream& os, Vector& v){
	for(auto& i : v){
		os << i << endl;
	}
	return os << endl;
}

int main(){
	Timing timer;
	Vector v;
	v.randomize(200);
	cout << v;
	v.countSort();
	cout << v;

	return system("pause");
}
