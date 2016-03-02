/*
编写者：李肇阳

创建日期：2015-03-27

语言：C++

编写及调试环境：Microsoft Visual Studio 2012 (Visual C++ 11.0)
*/


//计时器类
/*

*/


#ifndef TIMING_H
#define TIMING_H
#include <ctime>

class Timing
{
private:
	clock_t clockStart, clockEnd;
	int divisor; 

public:
	Timing();
	~Timing() {}

public:
	void start();
	void end();
	void reportCPUtime(); 
	double getCPUtime(); 
	void setDivisor(int t) {divisor=t;}
}; //end of class

#endif
