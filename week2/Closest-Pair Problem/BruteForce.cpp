#include "BruteForce.h"
Result BruteForce::solve(Points p){
	if(p.size() < 2)
		throw 2333;

	coordinate_t min = -1; //-1 for unassigned
	Point a, b;
	for(auto& i : p){
		for(auto& j : p){
			if(i.id == j.id)
				continue;
			coordinate_t d = distance(i, j);
			if(d < min || min == -1){
				min = d;
				a = i, b = j;
			}
		}
	}
	Result r = distance(a, b);
	return r;
}

BruteForce::BruteForce(void)
{
}


BruteForce::~BruteForce(void)
{
}
