/*
文件名: 
描　述: 数据结构习题10.30，非递归形式的快速排序
作　者: 李肇阳, 清华大学软件学院, lizy14@yeah.net
创建于: 2015年12月11日
环　境: Visual Studio 2012 (MSVC++ 11.0)

有删改 2016-03-08
*/

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

struct Range {
	int a, b;
	Range(int a_=0, int b_=0):a(a_),b(b_){}
};

template<class T>
void quickSort_(vector<T>& arr) {

	stack<Range> s; 

	int len = arr.size();
	s.push(Range(0, len - 1));

	while (!s.empty()) {
		Range range = s.top();
		s.pop();

		if(range.a >= range.b)
			continue;
		T mid = arr[range.b];
		int left = range.a, right = range.b - 1;
		while (left < right) {
			while (arr[left] < mid && left < right)
				left++;
			while (arr[right] >= mid && left < right)
				right--;
			std::swap(arr[left], arr[right]);
		}
		if (arr[left] >= arr[range.b])
			std::swap(arr[left], arr[range.b]);
		else
			left++;
		s.push(Range(range.a, left - 1));
		s.push(Range(left + 1, range.b));
	}
}