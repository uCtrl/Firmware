#ifndef UTILS_MATHUTILS_H_
#define UTILS_MATHUTILS_H_

#include "mbed.h"

class UMathUtils {

private:


public:

	static uint32_t gcd(uint32_t a, uint32_t b);
	static uint32_t gcdOfMultipleNumbers(uint32_t* values, uint32_t length);

};


#endif  // UTILS_MATHUTILS_H_
