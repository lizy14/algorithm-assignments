// Library.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Library.h"



// 有关类定义的信息，请参阅 Library.h
void LIBRARY_API __stdcall addPoint(int x, int y){
	static id_t id = 0;
	id++;
	Point _ = {id, x, y};
	points.push_back(_);
	if(id >= 2)
		result = dc.solve(points);
}

int LIBRARY_API getA(){
	return result.a;
}

int LIBRARY_API getB(){
	return result.b;
}
