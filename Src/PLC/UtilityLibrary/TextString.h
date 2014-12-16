#pragma once
#include "stdarg.h"
#include "mbed.h"
class TextString
{
private:
	int _Length;
	char * _Text;

	void Reset();

public:
	TextString(void);
	TextString(const TextString & string);
	TextString(int length);
	TextString(char * text);

	void Append(char * text);
	void Format(char * format, ...);
	void AppendFormat(char * format, ...);

	int GetLength() const { return _Length; }
	void ToLower();

	bool operator == (const TextString & other)const;
	operator char * () const { return _Text; }
	int Compare(char * text);
	TextString & operator = (const TextString &);
	TextString & operator = (const char * text);
	TextString Tokenize(char * token, int & curPos);
	virtual ~TextString(void);
};

