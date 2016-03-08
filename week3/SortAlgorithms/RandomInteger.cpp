#include "RandomInteger.h"

RandomInteger::RandomInteger(){
	assert(sizeof(unsigned int)==4); /*hard coded*/
	assert(RAND_MAX == 32767); /*hard coded*/
	std::srand(std::time(0));
}

unsigned int RandomInteger::get(){
	unsigned int r = 0;
	for(int i=0; i<3; i++){ /*hard coded*/
		r <<= 15; /*hard coded*/
		r += std::rand();
	}
	return r;
}
 