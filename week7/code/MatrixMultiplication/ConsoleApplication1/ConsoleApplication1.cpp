// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <vector>
#include "timing.h"
template <typename T>
class Matrix {
	T* _;
	
public:
	int d; //dimension
	Matrix(int d) {
		setSize(d);
		randomize();
	}
	~Matrix() {
		_aligned_free(_);
	}
	static void Mul(Matrix& a, Matrix& b, Matrix& c) {
		int d = a.d;
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < d; j++) {
				c.at(i,j) = 0;
				for (int k = 0; k < d; k++) {
					c.at(i,j) += a.at(i,j) * b.at(i,j);
				}
			}
		}
			
	}
	void setSize(int __) {
		d = __;
		int optimizedSize= ((sizeof(T) * d * d - 1) / 64 + 1) * 64;
		_ = (T*)_aligned_malloc(optimizedSize, 4096);
	}
	void randomize() {
		srand(12345);
		for (int i = 0; i < d; i++) {
			for (int j = 0; j < d; j++) {
				at(i,j) = rand();
			}
		}
	}
	T& at(int i, int j) {
		return _[i * d + j];
	}
};

int main()
{
	for (int N = 1; ; N *= 2) {
		cout << N << '\t';
		Timing timer;
			Matrix<double> a(N), b(N), c(N);
			if (N <= 16) {
				timer.setDivisor(100000);
				timer.start();
				for (auto i = 0; i < 100000; i++) {
					Matrix<double>::Mul(a, b, c);
				}
				timer.end();
			}
			else if(N<=64){
				timer.setDivisor(1000);
				timer.start();
				for (auto i = 0; i < 1000; i++) 
					Matrix<double>::Mul(a, b, c);
				timer.end();
			}else{
				timer.start();
					Matrix<double>::Mul(a, b, c);
				timer.end();
			}
			cout << timer.getCPUtime() << '\n';

	}
    return 0;
}

