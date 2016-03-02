/*
平面最近点对问题
李肇阳，2014013432，清华大学软件学院
VS2012
2016-03-01
*/

#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

typedef int id_t;
typedef int coordinate_t; 
typedef int distance_t;
struct Point{
	id_t id;
	coordinate_t x, y;
};

struct Result{
	id_t a, b;
	distance_t d; //distance squared
	operator distance_t(){
		return d;
	}
	bool operator==(Result c){
		if(c.d != d)
			return false;
		if(c.a == a && c.b == b)
			return true;
		if(c.b == a && c.a == b)
			return true;
		return false;
	}
};

typedef std::vector<Point> Points;

extern Points createProblem(int size);
extern Result distance(const Point& x, const Point& y); //squared Euclidean distance

extern std::ostream& operator<<(std::ostream& os, Result& r);