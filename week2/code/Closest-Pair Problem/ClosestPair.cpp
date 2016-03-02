#include "ClosestPair.h"

int rand_(){
	//return std::rand() << 15 | std::rand();
	return std::rand();
}

Points createProblem(int size){
	static bool flag = true;
	if(flag)
		std::srand(std::time(0)), flag = false;
	Points r;
	for(int i=0; i<size; i++){
		Point p = {i, rand_(), rand_()};
		r.push_back(p);
	}
	return r;
}

Result distance(const Point& x, const Point& y){
	coordinate_t deltaX = x.x - y.x;
	coordinate_t deltaY = x.y - y.y;
	Result r = {x.id, y.id, deltaX * deltaX + deltaY * deltaY};
	return r;
}


std::ostream& operator<<(std::ostream& os, Result& r){
	return os << r.a << ", " << r.b << ": " << std::sqrt(r.d) << endl;
}
