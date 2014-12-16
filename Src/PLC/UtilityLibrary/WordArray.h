#pragma once
#include "TextString.h"
#include "ByteArray.h"

class WordArray
{
	int _Size;
	UINT16 * _Array;

public:
	WordArray(void);
	WordArray(int size);
	WordArray(int size, BYTE * data);
	WordArray(int size, UINT16 * data);
	WordArray(const WordArray & byteArray);
	WordArray(ByteArray & data);

	virtual ~WordArray(void);
	virtual TextString ToString();
};

