#pragma once

#include "UPlcConfigFile.h"
#include "TextString.h"

class ByteArray
{
public:
	int _Size;
	BYTE * _Array;
public:
	ByteArray(void);
	ByteArray(int size);
	ByteArray(int size, BYTE * data);
	ByteArray(const ByteArray & byteArray);
	ByteArray(int count, ...);
	ByteArray(TextString tx);

	virtual ~ByteArray(void);
	virtual TextString ToString();
	virtual TextString ToString(char * format);
};
