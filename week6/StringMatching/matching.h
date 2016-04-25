/*
By Zhaoyang, April 2016.
*/

#pragma once
#include <vector>
typedef std::vector<unsigned int> result;
result BF(char *x, int m, char *y, int n);
result KMP(char *x, int m, char *y, int n);
result BM(char *x, int m, char *y, int n);


#include "timing.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

typedef result(*matcher) (char *x, int m, char *y, int n);
