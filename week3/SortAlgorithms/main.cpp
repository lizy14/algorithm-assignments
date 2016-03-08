/*
Algorithms Assignment #3,
By Zhaoyang, March 2016
*/


#include "timing.h"

#include <iostream>
#include <cstdlib>

using namespace std;

#define LENGTH (32) // 15, 30, 32
#define MAX ((((unsigned long long)1)<<(LENGTH))-1)

#include "SortAlgorithms.h"

int main(){
	Timing timer;
	Vector v;
	v.randomize(10);
	cout <<v << endl;
	v.radixSort();
	cout << v << endl;
	

	int sizes[] = {10,1e2,1e3,1e4,1e5,1e6,1e7,1e8,2e8};
	cout << "size\tinsertion\tmerge\tquick\tradix\n";
	for(auto size : sizes){
		cout << size << '\t';
		int totalTime, times;
		
		totalTime = 0, times = 0;
		while(0){
			v.randomize(size);
			timer.start();
			v.insertionSort();
			timer.end();
			times += 1;
			totalTime += timer.getCPUtime();
			if(totalTime > 1e5){
				cout << totalTime/(times+0.) << '\t';
				break;
			}
		}


		totalTime = 0, times = 0;
		while(1){
			v.randomize(size);
			timer.start();
			v.mergeSort();
			timer.end();
			times += 1;
			totalTime += timer.getCPUtime();
			if(totalTime > 1e5){
				cout << totalTime/(times+0.) << '\t';
				break;
			}
		}

		totalTime = 0, times = 0;
		while(1){
			v.randomize(size);
			timer.start();
			v.quickSort();
			timer.end();
			times += 1;
			totalTime += timer.getCPUtime();
			if(totalTime > 1e5){
				cout << totalTime/(times+0.) << '\t';
				break;
			}
		}


		totalTime = 0, times = 0;
		while(1){
			v.randomize(size);
			timer.start();
			v.radixSort();
			timer.end();
			times += 1;
			totalTime += timer.getCPUtime();
			if(totalTime > 1e5){
				cout << totalTime/(times+0.) << '\t';
				break;
			}
		}

		cout << '\n';
	}

	return system("pause");
}


