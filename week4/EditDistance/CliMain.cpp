#include "EditDistance.h"

#include <iostream>
int main(){
	//string a = "edit";
	//string b = "distance";

	string a = "appletree";
	string b = "a";
	Costs c;
	c[COPY] = 1;
	c[KILL] = 2;
	
	{
		EditDistance e(a,b,c);
		e.solve();
		std::cout << e.getCost() << std::endl;
		std::cout << e.getOperationsString() << std::endl;
	}{
		EditDistance e(b,a,c);
		e.solve();
		std::cout << e.getCost() << std::endl;
		std::cout << e.getOperationsString() << std::endl;
	}
	return system("pause");
}