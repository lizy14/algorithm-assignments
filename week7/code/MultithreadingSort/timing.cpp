/*
编写者：李肇阳

创建日期：2015-03-27

语言：C++

编写及调试环境：Microsoft Visual Studio 2012 (Visual C++ 11.0)
*/
#include "stdafx.h"
#include <iostream>
using namespace std;
#include "timing.h"

Timing::Timing():divisor(1)
{
	clockStart = clock();
	clockEnd = clockStart;
}//end function

void Timing::start()
{
	clockStart = clock();
	wallStart = std::chrono::system_clock::now();
}//end function
void Timing::end()
{
	clockEnd = clock();
	wallEnd = std::chrono::system_clock::now();
}//end function

void Timing::reportCPUtime()
{
	clock_t timeDelta = clockEnd - clockStart;
	double report = (double)timeDelta * (1000000 / CLOCKS_PER_SEC) / divisor;
	if(divisor==1){
	}else{
		cout << "运行了 " << divisor << " 次，平均每次";
	}
	cout << "所用 CPU 时间 " << report << " 微秒。" << endl;
}//end function

double Timing::getCPUtime()
{
	clock_t timeDelta = clockEnd - clockStart;
	return (double)timeDelta * (1000000 / CLOCKS_PER_SEC) / divisor;
}//end function


void Timing::reportWallTime()
{
	std::chrono::duration<double> elapsed_seconds = wallEnd - wallStart;
	if (divisor == 1) {
	}
	else {
		cout << "运行了 " << divisor << " 次，平均每次";
	}
	cout << "所用墙上时钟时间 " << elapsed_seconds.count() << " 秒。" << endl;
}//end function

double Timing::getWallTime()
{
	std::chrono::duration<double> elapsed_seconds = wallEnd - wallStart;
	return 1e6*elapsed_seconds.count();
}//end function
