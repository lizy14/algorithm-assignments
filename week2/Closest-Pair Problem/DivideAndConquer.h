/*
平面最近点对问题，分治递归 O (n lg n)
李肇阳，2014013432，清华大学软件学院
VS2012
2016-03-01
*/
#pragma once
#include "ClosestPair.h"
#include <algorithm>

struct Boundary{
	id_t l, r; //including left, excluding right
};
class DivideAndConquer
{
public:
	DivideAndConquer(void);
	~DivideAndConquer(void);
	Result solve(Points& p);
	Result recursive(Points&, Boundary);
};

