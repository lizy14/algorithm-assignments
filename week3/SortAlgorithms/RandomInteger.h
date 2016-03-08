/*

随机大整数发生器，指定 bit 数

支持不同编译器，不同的 RAND_MAX 和 sizeof(unsigned)

By Zhaoyang, March 2016
*/

#pragma once

#include <cstdlib>
#include <ctime>
#include <cassert>

class RandomInteger{
public:
	int _size;
	int _randSize;
	RandomInteger(int); //number of bits
	unsigned get();
};
