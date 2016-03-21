#include "EditDistance.h"

#include <iostream>
int main(){
	//string a = "edit";
	//string b = "distance";

	string a = "ab";
	string b = "ba";
	Costs c;
	c[COPY] = 1;
	c[KILL] = 2;
	c[TWIDDLE] = 99;
	{
		EditDistance e(a,b,c);
		e.solve();
		std::cout << e.getCost() << std::endl;
		std::cout << e.getOperationsString() << std::endl;
	}{
		EditDistance e(b,a,c);
		e.solve();
		std::cout << e.getCost() << std::endl;
	}
	return system("pause");
}