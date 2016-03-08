/*

随机数发生器

range [0, 2^32)

MSVC++ 11.0

By Zhaoyang, March 2016
*/

#pragma once

#include <cstdlib>
#include <ctime>
#include <cassert>

class RandomInteger{
public:
	RandomInteger();
	unsigned int get();
};
