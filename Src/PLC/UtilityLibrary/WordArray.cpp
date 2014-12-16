#include "WordArray.h"


WordArray::WordArray(void)
{
	_Size = 0;
	_Array = NULL;
}

WordArray::WordArray(int size)
{
	_Size = size;
	_Array = new UINT16[_Size];
}

WordArray::WordArray(int size, BYTE * data)
{
	_Size = ((size + 1) >> 1) ;
	_Array = new UINT16[_Size];

	for(int index=0, arrayIndex =0; index < size; index+= 2, arrayIndex++)
	{
		_Array[arrayIndex] = *((UINT16 *) & data[index]);
	}
}

WordArray::WordArray(int size, UINT16 * data)
{
	_Size = size ;
	_Array = new UINT16[_Size];

	for(int index=0; index < size; index++)
	{
		_Array[index] = data[index];
	}
}

WordArray::WordArray(const WordArray & wordArray)
{
	_Size = wordArray._Size;
	_Array = new UINT16[_Size];

	memcpy(_Array, wordArray._Array, sizeof(_Array)*2);
}

WordArray::WordArray(ByteArray & data)
{
	_Size = ((data._Size + 1) >> 2);
	_Array = new UINT16[_Size];

	memset(_Array, 0, _Size * 2);
	memcpy(_Array, data._Array, data._Size);
}

WordArray::~WordArray(void)
{
	if (_Array != NULL)
	{
		delete [] _Array;
	}
}

TextString WordArray::ToString()
{
	TextString temp;
	if (_Array == NULL || _Size == 0)
	{
		temp.Append("Empty");
	}
	else
	{
		temp.Format("0x%4.4X ", _Array[0]);
		for(int index=1; index < _Size; index++)
		{
			temp.AppendFormat("%4.4X ", _Array[index]);
			if ((index % 8) == 0)
			{
				temp.Append("\r\n");
			}
		}
	}
	return temp;
}