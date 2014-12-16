#pragma GCC diagnostic ignored "-Wwrite-strings"
#include <stdio.h>
#include <string.h>

#include "ByteArray.h"
//#include "stdarg.h"

ByteArray::ByteArray(void)
{
	_Size = 0;
	_Array = NULL;
}

ByteArray::ByteArray(int size)
{
	_Size = size;
	_Array = new BYTE[size];
}

ByteArray::ByteArray(int size, BYTE * data)
{
	_Size = size;
	_Array = NULL;
	if (size > 0)
	{
		_Array = new BYTE[size];
		memcpy(_Array, data, size);
	}
}
ByteArray::ByteArray(const ByteArray & byteArray)
{
	_Size = byteArray._Size;
	_Array = new BYTE[_Size];
	memcpy(_Array, byteArray._Array, _Size);
}

ByteArray::ByteArray(int count, ...)
{
	_Array = new BYTE[count];
	va_list listPointer;
	
	va_start(listPointer, count);

	for(int index=0; index < count; index++)
	{
		BYTE value = va_arg(listPointer, BYTE);
		_Array[index] = value;
	}

	va_end(listPointer);

}

ByteArray::ByteArray(TextString ts)
{
	int curPos = 0;
	if (ts[0] == 'x' || ts[0] == 'X')
	{
		curPos = 1;
	}
	else if (ts[1] == 'x' || ts[1] == 'X')
	{
		curPos = 2;
	}

	// remove any spaces
	TextString newTextString;
	while (curPos < ts.GetLength())
	{
		newTextString.Append(ts.Tokenize(" .", curPos));
	}

	int len = newTextString.GetLength();
	BYTE * tempArray = new BYTE[len];
	int offset=0;
	char *strPointer = (char*)newTextString;
	for(int index = 0; index < len; index+=2)
	{
		int i = 0;
		char * temp = (char *)(strPointer+index);
		sscanf((char*)temp, "%2x", & i);
		tempArray[offset++] = (BYTE)i;
	}

	_Size = offset;
	_Array = new BYTE[_Size];
	memcpy(_Array, tempArray, _Size);
	delete tempArray;
}

ByteArray::~ByteArray(void)
{
	if (_Array != NULL)
	{
		delete [] _Array;
	}
}

TextString ByteArray::ToString()
{
	TextString temp;
	if (_Array == NULL || _Size == 0)
	{
		temp.Append("Empty");
	}
	else if (_Size <= 16)
	{
		for(int index=0; index < _Size; index++)
		{
			if (index == 0)
			{
				temp.AppendFormat("0x%2.2X ", _Array[index]);
			}
			else
			{
				temp.AppendFormat("%2.2X ", _Array[index]);
			}
		}
	}
	else 
	{
		for(int index=0; index < _Size; index++)
		{
			if (index == 0)
			{
				temp.AppendFormat("0x%2.2X ", _Array[index]);
			}
			else if ((index % 20) == 0)
			{
				temp.AppendFormat("\r\n");
				temp.AppendFormat("0x%2.2X ", _Array[index]);
			}
			else if ((index % 10)== 0)
			{
				temp.Append("  ");
				temp.AppendFormat("0x%2.2X ", _Array[index]);
			}
			else
			{
				temp.AppendFormat("%2.2X ", _Array[index]);
			}
		}
	}
	return temp;
}
TextString ByteArray::ToString(char * format)
{
	TextString temp;
	if (_Array == NULL || _Size == 0)
	{
		temp.Append("Empty");
	}
	else
	{
		for(int index=0; index < _Size; index++)
		{
			temp.AppendFormat(format, _Array[index]);
		}
	}
	return temp;
}
