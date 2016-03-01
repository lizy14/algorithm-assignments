#include "DivideAndConquer.h"


Result DivideAndConquer::solve(Points& p){
	
	//sort by x coordinate
	std::sort(p.begin(), p.end(), [](Point a, Point b){
		return a.x < b.x;
	});
	
	Boundary b = {0, p.size()};
	return recursive(p, b);
}

Result DivideAndConquer::recursive(Points& p, Boundary b){
	
	if(b.l >= b.r - 1)
		throw 234;

	//bottom
	if(b.l == b.r - 2){
		Result r = distance(p[b.l], p[b.l + 1]);
		return r;
	}
	
	//bottom
	if(b.l == b.r - 3){
		Result r = distance(p[b.l], p[b.l + 1]);
		Result _;
		_ = distance(p[b.l], p[b.l + 2]);
		_ = _<r? _: r;
		_ = distance(p[b.l + 1], p[b.l + 2]);
		_ = _<r? _: r;
		return r;
	}

	//DIVIDE
	int m = (b.r + b.l) / 2;

	Boundary bl = {b.l, m};
	Boundary br = {m, b.r};

	//CONQUER
	Result rl = recursive(p, bl);
	Result rr = recursive(p, br);

	//COMBINE
	Result rm = rl<rr? rl: rr;
	coordinate_t d = std::sqrt(rm.d);
	
	//find boundary of neighbor
	int l, r;

	/*

	b.r    l    m    r     b.l

	*/
	for(l=b.l; l<b.r; l++)
		if(p[l].x >= p[m].x - d)
			break;

	for(r=b.r-1; r>b.l; r--)
		if(p[r].x <= p[m].x + d)
			break;

	Points neighbor; //points in neighborhood of mid-line
	for(int i=l; i<r; i++)
		neighbor.push_back(p[i]);

	//sort by y coordinate
	std::sort(neighbor.begin(), neighbor.end(), [](Point a, Point b){
		return a.y < b.y;
	});

	for(int i=0; i<neighbor.size(); i++){
		for(int j=1; j<=7/**/; j++){
			if( (i+j) >= neighbor.size() )
				break;
			Result _ = distance(neighbor[i], neighbor[i+j]);
			if(_ < rm)
				rm = _;
		}
	}

	return rm;
}

DivideAndConquer::DivideAndConquer(void)
{
}


DivideAndConquer::~DivideAndConquer(void)
{
}
