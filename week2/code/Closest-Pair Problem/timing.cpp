/*
编写者：李肇阳

创建日期：2015-03-27

语言：C++

编写及调试环境：Microsoft Visual Studio 2012 (Visual C++ 11.0)
*/

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
}//end function
void Timing::end()
{
	clockEnd = clock();
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
