#include "RandomInteger.h"

RandomInteger::RandomInteger(int size):_size(size),_randSize(0){
	assert((sizeof(unsigned)*8) >= _size);
	
	/*
	RAND_MAX == 32767 -> 15
	*/

	unsigned _ = RAND_MAX;
	
	while(1){
		if(_ & 1);else{
			assert(_ == 0);
			break;
		}
		
		_randSize++;
		_ >>= 1;
	}
	
	std::srand(std::time(0));
}

unsigned RandomInteger::get(){
	unsigned r = 0;
	for(int i=0; i<_size; i+=_randSize){
 		r <<= _randSize; 
		r += std::rand();
	}
	return r ;//% (1 << _size);
}
 