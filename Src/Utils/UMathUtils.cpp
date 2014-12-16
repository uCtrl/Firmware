#include "UMathUtils.h"

int UMathUtils::gcd(int a, int b)
{
	if(a == 0 || b == 0)
		return a+b;

	return gcd(b,a%b);
}

int UMathUtils::gcdOfMultipleNumbers(int* values, int length)
{
    int lastGcd = values[0];
    if(length > 1) {
        lastGcd = gcd(values[0], values[1]);
        for(int i = 1; i < length; i++) {
            lastGcd = gcd(values[i], lastGcd);
        }
    }
    return lastGcd;
}

int UMathUtils::power( int val, int _pow ) 
{
	if ( _pow <= 0 )
		return 1;
	return val * power( val, _pow-1 );
}

