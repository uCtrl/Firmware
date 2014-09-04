#include "UMathUtils.h"

uint32_t UMathUtils::gcd(uint32_t a, uint32_t b)
{
	if(a == 0 || b == 0)
		return a+b;

	return gcd(b,a%b);
}

uint32_t UMathUtils::gcdOfMultipleNumbers(uint32_t* values, uint32_t length)
{
    uint32_t lastGcd = values[0];
    if(length > 1) {
        lastGcd = gcd(values[0], values[1]);
        for(uint32_t i = 1; i < length; i++) {
            lastGcd = gcd(values[i], lastGcd);
        }
    }
    return lastGcd;
}
