#ifndef UTILS_MATHUTILS_H_
#define UTILS_MATHUTILS_H_

#include "mbed.h"

class UMathUtils {

private:


public:

	static int gcd(int a, int b);
	static int gcdOfMultipleNumbers(int* values, int length);

};


#endif  // UTILS_MATHUTILS_H_
