/*
平面最近点对问题，平凡 O (n^2)
李肇阳，2014013432，清华大学软件学院
VS2012
2016-03-01
*/

#pragma once
#include "ClosestPair.h"

class BruteForce
{
public:
	BruteForce(void);
	~BruteForce(void);
	Result solve(Points p);
};

